#include "GameScene.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
#include "TileMap.h"
#include "UIManager.h"
#include "EnemyManager.h"
#include "BasicTank.h"
#include "SpeedTank.h"
#include "PowerTank.h"
#include "ArmorTank.h"
#include "Ammo.h"
#include "AmmoManager.h"
#include "ItemManager.h"
#include "EnemyTank.h"


HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);
	m_backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

	m_gameOver = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Game_Over.bmp");

	mb_isGameOver = false;
	mb_isTimeStop = false;
	m_goElapsedTime = 0.0f;

	m_gameOverPos.x = TILE_MAP_START_POS_X + TILE_MAP_SIZE_X / 2;
	m_gameOverPos.y = TILE_MAP_SIZE_Y;
	m_tileMap = new TileMap;
	m_tileMap->Init();

	m_player = new Tank;
	m_player->Init();

	m_player->SetTileMap(m_tileMap);

	m_ammoMgr = new AmmoManager;
	m_ammoMgr->Init();
	m_ammoMgr->SetTileMap(m_tileMap);
	m_ammoMgr->SetIsGameOver(&mb_isGameOver);

	m_enemyMgr = new EnemyManager;
	m_enemyMgr->Init();
	m_enemyMgr->SetGameScene(this);
	m_enemyMgr->SetPlayerTank(m_player);
	m_enemyMgr->SetAmmoMgr(m_ammoMgr);

	m_itemMgr = new ItemManager;
	m_itemMgr->Init();
	m_itemMgr->SetGameScene(this);

	m_enemySpawnPlaceX = 0;
	m_enemyNumCount = 0;
	m_elapsedTime = 0;
	m_fireTime = 0;

	m_spawnPlaceX1 = (m_tileMap->GetShape().right - m_tileMap->GetShape().left) / 2;
	m_spawnPlaceX2 = m_tileMap->GetShape().right - 32;
	m_spawnPlaceX3 = m_tileMap->GetShape().left + 32;
	m_spawnPlaceY = m_tileMap->GetShape().top + 32;
	
	switch (GameManager::GetSingleton()->GetStageNr())
	{
	case 1:
		m_enemyTotNum = 1; break;
	case 2:
		m_enemyTotNum = 1; break;
	}

	m_uiManager = new UIManager;
	m_uiManager->Init(m_enemyTotNum);

	m_itemTime = 0;

	return S_OK;
}

void GameScene::Update()
{
	if (m_player->GetHP() == 0)
	{
		mb_isGameOver = true;
	}

	if (mb_isGameOver)
	{
		m_goElapsedTime += TimerManager::GetSingleton()->GetDeltaTime();
		if (m_gameOverPos.y > TILE_MAP_START_POS_Y + TILE_MAP_SIZE_Y / 2)
		{
			m_gameOverPos.y -= 2;
		}
		else
		{
			// 게임오버
			Sleep(1000);
			GameManager::GetSingleton()->SetPlayerHp(m_player->GetHP());
			SceneManager::GetSingleton()->ChangeScene("결과씬");
		}
		if(m_goElapsedTime > 0.4f)
			return;
	}

	m_tileMap->Update();

	// 적 생성 
	if (!mb_isTimeStop)
	{
		m_elapsedTime += TimerManager::GetSingleton()->GetDeltaTime();
		if (m_elapsedTime > 3.0f && m_enemyNumCount < m_enemyTotNum)
		{
			SpawnEnemy();
			m_elapsedTime = 0;
		}
	}

	m_uiManager->Update(m_enemyTotNum, m_enemyNumCount, m_player->GetHP());

	// 아이템 매니저 업데이트
	m_itemMgr->Update();
	m_itemTime += TimerManager::GetSingleton()->GetDeltaTime();
	if (m_itemTime > 10.0f)
	{
		m_itemMgr->AddItem();
		m_itemTime = 0.0f;
	}

	// 플레이어, 플레이어 아모발사, 플레이어 아모 매니저 업데이트
	if (m_player->GetAlive() == true)
	{
		m_player->Update();
	}

	m_ammoMgr->SetVecEnemys(m_enemyMgr->GetVecEnemys());
	m_ammoMgr->Update();

	if (m_player->GetisFire())
	{
		m_ammoMgr->AddAmmo(new Ammo, m_player);
		m_player->SetisFire(false);
	}

	// 에너미 , 에너미 아모발사, 에너미 아모 매니저 업데이트
	m_enemyMgr->Update();

	// 스테이지 클리어
	if (GameManager::GetSingleton()->GetKillCount()->totKillTankNr == m_enemyTotNum && m_enemyMgr->GetVecEnemys().empty())
	{
		Sleep(2000);
		GameManager::GetSingleton()->SetPlayerHp(m_player->GetHP());
		GameManager::GetSingleton()->SetPlayerFrameY(m_player->GetFrameY());
		SceneManager::GetSingleton()->ChangeScene("결과씬");
	}
}

void GameScene::Render(HDC hdc)
{
	m_backGround->Render(hdc);

	m_tileMap->Render(hdc);
	m_uiManager->Render(hdc);

	if (m_player->GetAlive() == true)
	{
		m_player->Render(hdc);
	}

	m_enemyMgr->Render(hdc);

	m_ammoMgr->Render(hdc);

	m_itemMgr->Render(hdc);

	// 풀 타일 출력
	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			if(m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].terrain == Terrain::Grass)
				m_tileMap->GetTileImage()->Render(hdc,
					m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].rc.left + TILE_SIZE / 2,
					m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].rc.top + TILE_SIZE / 2,
					m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].frameX,
					m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].frameY);
		}
	}

	if (mb_isGameOver)
	{
		m_gameOver->Render(hdc, m_gameOverPos.x, m_gameOverPos.y);
	}
}

void GameScene::Release()
{
	//SAFE_RELEASE(m_backGround);
	//SAFE_RELEASE(m_gameOver);
	SAFE_RELEASE(m_tileMap);
	SAFE_RELEASE(m_uiManager);
	SAFE_RELEASE(m_player);
	SAFE_RELEASE(m_ammoMgr);
	SAFE_RELEASE(m_enemyMgr);
	SAFE_RELEASE(m_itemMgr);
}

void GameScene::SpawnEnemy()
{
	if ((m_enemyNumCount % 3) == 0) { m_enemySpawnPlaceX = m_spawnPlaceX1; }
	else if ((m_enemyNumCount % 3) == 1) { m_enemySpawnPlaceX = m_spawnPlaceX2; }
	else if ((m_enemyNumCount % 3) == 2) { m_enemySpawnPlaceX = m_spawnPlaceX3; }

	switch (m_enemyNumCount % 4)
	{
	case 0:
		m_enemyMgr->AddEnemy(new BasicTank(m_tileMap), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
		m_enemyNumCount++;
		break;

	case 1:
		m_enemyMgr->AddEnemy(new SpeedTank(m_tileMap), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
		m_enemyNumCount++;
		break;

	case 2:
		m_enemyMgr->AddEnemy(new PowerTank(m_tileMap), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
		m_enemyNumCount++;
		break;

	case 3:
		m_enemyMgr->AddEnemy(new ArmorTank(m_tileMap), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
		m_enemyNumCount++;
		break;
	}
}
