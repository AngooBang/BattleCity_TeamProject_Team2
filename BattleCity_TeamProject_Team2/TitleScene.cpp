#include "TitleScene.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	m_pos.x = 500;
	m_pos.y = 1350;
	m_moveSpeed = 5;

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	m_title = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Title.bmp");

	ImageManager::GetSingleton()->AddImage("Image/backGround2.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	m_backGround2 = ImageManager::GetSingleton()->FindImage("Image/backGround2.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	m_enemyType = ImageManager::GetSingleton()->FindImage("Image/Enemy.bmp");

	return S_OK;
}
void TitleScene::AutoMove()
{
	m_pos.y -= m_moveSpeed;
	if (m_pos.y == 450)
		m_moveSpeed = 0;
}

void TitleScene::Update()
{
	AutoMove();
	if (m_moveSpeed == 0)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			SceneManager::GetSingleton()->ChangeScene("½ºÅ×ÀÌÁö¾À");
		}
		else
		{
			return;
		}
	}
}

void TitleScene::Render(HDC hdc)
{
	m_backGround2->Render(hdc);
	m_title->Render(hdc, m_pos.x, m_pos.y);
	if (m_moveSpeed == 0)
	{
		m_enemyType->Render(hdc, 250, 530, 6, 5);
	}
}

void TitleScene::Release()
{
}


