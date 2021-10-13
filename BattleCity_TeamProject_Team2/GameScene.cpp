#include "GameScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TileMap.h"
#include "UIManager.h"

HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);


	m_backGround = ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	m_tileMap = new TileMap;
	m_tileMap->Init();

	m_uiManager = new UIManager;
	m_uiManager->Init();

	return S_OK;
}

void GameScene::Update()
{

	m_tileMap->Update();
	m_uiManager->Update();
}

void GameScene::Render(HDC hdc)
{

	m_backGround->Render(hdc);

	m_tileMap->Render(hdc);
	m_uiManager->Render(hdc);

}

void GameScene::Release()
{
	SAFE_RELEASE(m_backGround);
	SAFE_RELEASE(m_tileMap);
	SAFE_RELEASE(m_uiManager);
}
