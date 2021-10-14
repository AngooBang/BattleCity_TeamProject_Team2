#include "ResultScene.h"
#include "Image.h"

HRESULT ResultScene::Init()
{

	m_backGround = ImageManager::GetSingleton()->AddImage("Image/backGround.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	return S_OK;
}

void ResultScene::Update()
{
}

void ResultScene::Render(HDC hdc)
{
	m_backGround->Render(hdc);
}

void ResultScene::Release()
{
	SAFE_RELEASE(m_backGround);
}
