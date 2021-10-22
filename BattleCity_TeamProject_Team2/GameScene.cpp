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

#include "EnemyTank.h"


HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);

	m_backGround = ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	m_gameOver = ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Game_Over.bmp", 96, 45, true, RGB(255, 0, 255));

	mb_isGameOver = false;
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
	m_enemyMgr->SetPlayerTank(m_player);

	m_enemyMgr->SetTileMap(m_tileMap);	// 맵과 적탱크 충돌처리 하기위해 데이터 갖고오기 위해 만들어 놓은 실험용.
	//m_enemyMgr->CollisionWithTile();

	m_spawnPlaceX1 = (m_tileMap->GetShape().right - m_tileMap->GetShape().left) / 2;
	m_spawnPlaceX2 = m_tileMap->GetShape().right - 32;
	m_spawnPlaceX3 = m_tileMap->GetShape().left + 32;
	m_spawnPlaceY = m_tileMap->GetShape().top + 32;
	
	m_stageNum = m_tileMap->GetStageNum();
	
	switch (m_stageNum)
	{
	case 1:
		m_enemyTotNum = 12;
		m_basicTankNum = 3;
		m_speedTankNum = 3;
		m_powerTankNum = 3;
		m_armorTankNum = 3;
		break;
	}

	m_uiManager = new UIManager;
	m_uiManager->Init(m_enemyTotNum);

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
			SceneManager::GetSingleton()->ChangeScene("결과씬");
		}
		if(m_goElapsedTime > 0.4f)
			return;
	}
	m_tileMap->Update();


	m_elapsedTime += TimerManager::GetSingleton()->GetDeltaTime();

	// 적 생성 
	if (m_elapsedTime > 3.0f && m_enemyNumCount < m_enemyTotNum)
	{	
		if ((m_enemyNumCount % 3) == 0 ) { m_enemySpawnPlaceX = m_spawnPlaceX1; }
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
		// 아모매니저, 아모에 vector<EnemyTank*> 갱신
		m_elapsedTime = 0;
	}

	m_uiManager->Update(m_enemyTotNum, m_enemyNumCount, m_player->GetHP());

	// 에너미 , 에너미 아모발사, 에너미 아모 매니저 업데이트
	m_enemyMgr->Update();



	m_vecEnemyTank = m_enemyMgr->GetVecEnemys();
	if (!m_vecEnemyTank.empty())
	{
		for (m_it = m_vecEnemyTank.begin(); m_it != m_vecEnemyTank.end(); m_it++)
		{
			if ((*m_it)->GetisFire() == true)
			{
				m_ammoMgr->AddAmmo(new Ammo, m_it, m_player);
				(*m_it)->SetisFire(false);
			}
		}
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


	if (GameManager::GetSingleton()->GetKillCount()->totKillTankNr == m_enemyTotNum)
	{
		// 스테이지 클리어
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
}
