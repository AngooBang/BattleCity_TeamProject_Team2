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


HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);

	m_backGround = ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	m_tileMap = new TileMap;
	m_tileMap->Init();

	m_uiManager = new UIManager;
	m_uiManager->Init();

	m_player = new Tank;
	m_player->Init();

	m_player->SetTileMap(m_tileMap);

	m_ammoMgr = new AmmoManager;
	m_ammoMgr->Init();

	m_enemyMgr = new EnemyManager;
	m_enemyMgr->Init();

	m_enemyMgr->SetTileMap(m_tileMap);	// 맵과 적탱크 충돌처리 하기위해 데이터 갖고오기 위해 만들어 놓은 실험용.
	//m_enemyMgr->CollisionWithTile();

	m_mapShape = m_tileMap->GetShape();

	m_spawnPlaceX1 = (m_mapShape.right - m_mapShape.left) / 2;
	m_spawnPlaceX2 = m_mapShape.right - 32;
	m_spawnPlaceX3 = m_mapShape.left + 32;
	m_spawnPlaceY = m_mapShape.top + 32;
	
	m_stageNum = m_tileMap->GetStageNum();
	
	switch (m_stageNum)
	{
	case 1:
		m_enemyTotNum = 20;
		m_basicTankNum = 5;
		m_speedTankNum = 5;
		m_powerTankNum = 5;
		m_armorTankNum = 5;
		break;
	}

	return S_OK;
}

void GameScene::Update()
{
	m_tileMap->Update();
	m_uiManager->Update();

	m_player->KeyUpdate();
	m_player->Update();

	// 적 생성 
	m_elapsedTime += TimerManager::GetSingleton()->GetDeltaTime();
	if (m_elapsedTime > 3.0f && m_enemyNumCount <= m_enemyTotNum)
	{	
		if ((m_enemyNumCount % 3) == 0 ) { m_enemySpawnPlaceX = m_spawnPlaceX1; }
		else if ((m_enemyNumCount % 3) == 1) { m_enemySpawnPlaceX = m_spawnPlaceX2; }
		else if ((m_enemyNumCount % 3) == 2) { m_enemySpawnPlaceX = m_spawnPlaceX3; }

		switch (m_enemyNumCount % 4)
		{
		case 0:
			m_enemyMgr->AddEnemy(new BasicTank(m_mapShape), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
			m_enemyNumCount++;
			break;
		
		case 1:
			m_enemyMgr->AddEnemy(new SpeedTank(m_mapShape), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
			m_enemyNumCount++;
			break;

		case 2:
			m_enemyMgr->AddEnemy(new PowerTank(m_mapShape), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
			m_enemyNumCount++;
			break;

		case 3:
			m_enemyMgr->AddEnemy(new ArmorTank(m_mapShape), POINTFLOAT{ m_enemySpawnPlaceX, m_spawnPlaceY });
			m_enemyNumCount++;
			break;
		}
		m_elapsedTime = 0;
	}

	m_enemyMgr->Update();


	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
		SceneManager::GetSingleton()->ChangeScene("결과씬");

}

void GameScene::Render(HDC hdc)
{

	m_backGround->Render(hdc);

	m_tileMap->Render(hdc);
	m_uiManager->Render(hdc);

	m_player->Render(hdc);

	m_enemyMgr->Render(hdc);

	m_ammoMgr->Render(hdc);
}

void GameScene::Release()
{
	SAFE_RELEASE(m_backGround);
	SAFE_RELEASE(m_tileMap);
	SAFE_RELEASE(m_uiManager);
	SAFE_RELEASE(m_player);
	//SAFE_RELEASE(m_enemyMgr);
}
