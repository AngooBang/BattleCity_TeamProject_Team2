#include "GameScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "UIManager.h"
#include "EnemyTank.h"

HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);


	m_backGround = ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);


	m_uiManager = new UIManager;
	m_uiManager->Init();

	enemyTank = new EnemyTank;
	enemyTank->Init();

	return S_OK;
}

void GameScene::Update()
{
	m_uiManager->Update();
	enemyTank->Update();
}

void GameScene::Render(HDC hdc)
{

	m_backGround->Render(hdc);
	m_uiManager->Render(hdc);

	enemyTank->Render(hdc);
}

void GameScene::Release()
{
	SAFE_RELEASE(m_backGround);	
	SAFE_RELEASE(m_uiManager);
	SAFE_RELEASE(enemyTank);
}
