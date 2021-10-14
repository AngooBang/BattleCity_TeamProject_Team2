#include "PlayerTank.h"

HRESULT PlayerTank::Init()
{
	//m_imageData[Left] = new Image;
	//m_imageData[Right] = new Image;
	//m_imageData[Up] = new Image;
	//m_imageData[Down] = new Image;

	//m_imageData[Left]->Init("Image/BattleCity/Player/Player.bmp",)
	//m_imageData[Right]->Init;
	//m_imageData[Up]->Init;
	//m_imageData[Down]->Init;

	m_ImageData = ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256,false,RGB(255,0,255));

	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y / 2;

	m_moveDir = MoveDir::Up;
	m_Barrelend.x = pos.x;
	m_Barrelend.y = pos.y - 32;

	bodySize = 64;

	moveSpeed = 10;

	return S_OK;
}

void PlayerTank::KeyUpdate()
{
#pragma region ÀÔ·ÂºÎ

	if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)))
	{
		m_moveDir = MoveDir::Left;
		mb_Move = true;
	}
	else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)))
	{
		m_moveDir = MoveDir::Right;
		mb_Move = true;
	}
	else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_UP)))
	{
		m_moveDir = MoveDir::Up;
		mb_Move = true;
	}
	else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)))
	{
		m_moveDir = MoveDir::Down;
		mb_Move = true;
	}
	else
	{
		mb_Move = false;
	}

#pragma endregion
}

void PlayerTank::Render(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
}
