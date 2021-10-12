#include "GameScene.h"
#include "CommonFunction.h"

HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);

	return S_OK;
}

void GameScene::Update()
{
}

void GameScene::Render(HDC hdc)
{
}

void GameScene::Release()
{
}
