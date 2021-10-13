#include "GameScene.h"
#include "CommonFunction.h"
#include "EnemyTank.h"

HRESULT GameScene::Init()
{
	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);

	enemyTank = new EnemyTank;
	enemyTank->Init();

	return S_OK;
}

void GameScene::Update()
{
	enemyTank->Update();
}

void GameScene::Render(HDC hdc)
{
	enemyTank->Render(hdc);
}

void GameScene::Release()
{
	SAFE_RELEASE(enemyTank);
}
