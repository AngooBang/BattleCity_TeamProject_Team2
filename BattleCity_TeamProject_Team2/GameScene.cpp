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

	m_tileMap = new TileMap;
	m_tileMap->Init();

	m_player = new Tank;
	m_player->Init();

	m_player->SetTileMap(m_tileMap);

	m_ammoMgr = new AmmoManager;
	m_ammoMgr->Init();
	m_ammoMgr->SetTileMap(m_tileMap);

	// 테스트용
	m_enemyAmmoMgr = new AmmoManager;
	m_enemyAmmoMgr->Init();
	m_enemyAmmoMgr->SetTileMap(m_tileMap);
	m_enemyAmmoMgr->SetTarget(m_player);

	m_enemyMgr = new EnemyManager;
	m_enemyMgr->Init(m_enemyAmmoMgr);
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
	m_tileMap->Update();

	if (m_player->GetAlive() == true)
	{
		m_player->Update();
	}

	// 적 생성 
	m_elapsedTime += TimerManager::GetSingleton()->GetDeltaTime();
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
		m_elapsedTime = 0;
	}

	m_uiManager->Update(m_enemyTotNum, m_enemyNumCount);
	m_enemyMgr->Update();

	m_vecEnemyTank = m_enemyMgr->GetEnemyVec();
	if (!m_vecEnemyTank.empty())
	{
		for (m_it = m_vecEnemyTank.begin(); m_it != m_vecEnemyTank.end(); m_it++)
		{
			if ((*m_it)->GetisFire() == true)
			{
				m_enemyAmmoMgr->AddAmmo(new Ammo, m_it, m_player);
				(*m_it)->SetisFire(false);
			}
		}
	}
	
	m_enemyAmmoMgr->Update();
	


	if (m_player->GetisFire())
	{
		m_ammoMgr->AddAmmo(new Ammo, m_player);
		m_player->SetisFire(false);
	}

	m_ammoMgr->Update();

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
		SceneManager::GetSingleton()->ChangeScene("결과씬");

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
	m_enemyAmmoMgr->Render(hdc);
}

void GameScene::Release()
{
	SAFE_RELEASE(m_backGround);
	SAFE_RELEASE(m_tileMap);
	SAFE_RELEASE(m_uiManager);
	SAFE_RELEASE(m_player);
	SAFE_RELEASE(m_ammoMgr);
	//SAFE_RELEASE(m_enemyMgr);
}
