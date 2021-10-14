#include "GameScene.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "PlayerTank.h"
#include "Image.h"
#include "TileMap.h"
#include "UIManager.h"
#include "EnemyManager.h"
#include "BasicTank.h"
#include "SpeedTank.h"
#include "PowerTank.h"
#include "ArmorTank.h"


HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);

	m_backGround = ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);


	m_tileMap = new TileMap;
	m_tileMap->Init();

	m_uiManager = new UIManager;
	m_uiManager->Init();

	m_player = new PlayerTank;
	m_player->Init();

	m_enemyMgr = new EnemyManager;
	m_enemyMgr->Init();
	m_enemyMgr->AddEnemy(new BasicTank, POINTFLOAT{ WIN_SIZE_X / 5, WIN_SIZE_Y / 5 });
	m_enemyMgr->AddEnemy(new SpeedTank, POINTFLOAT{ WIN_SIZE_X * 4 / 5, WIN_SIZE_Y * 4 / 5 });
	m_enemyMgr->AddEnemy(new PowerTank, POINTFLOAT{ WIN_SIZE_X / 5, WIN_SIZE_Y * 4 / 5 });
	m_enemyMgr->AddEnemy(new ArmorTank, POINTFLOAT{ WIN_SIZE_X * 4 / 5, WIN_SIZE_Y / 5 });

	return S_OK;
}

void GameScene::Update()
{
	m_tileMap->Update();
	m_uiManager->Update();

	m_player->Update();
	//m_enemyMgr->AddEnemy(new BasicTank, POINTFLOAT{WIN_SIZE_X / 5, WIN_SIZE_Y / 5});
	m_enemyMgr->Update();
}

void GameScene::Render(HDC hdc)
{

	m_backGround->Render(hdc);

	m_tileMap->Render(hdc);
	m_uiManager->Render(hdc);

	m_player->Render(hdc);

	m_enemyMgr->Render(hdc);
}

void GameScene::Release()
{
	SAFE_RELEASE(m_backGround);
	SAFE_RELEASE(m_tileMap);
	SAFE_RELEASE(m_uiManager);
	SAFE_RELEASE(m_player);
	SAFE_RELEASE(m_enemyMgr);
}
