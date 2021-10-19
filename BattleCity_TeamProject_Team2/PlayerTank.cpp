#include "PlayerTank.h"

HRESULT PlayerTank::Init()
{
<<<<<<< HEAD
	//m_imageData[Left] = new Image;
	//m_imageData[Right] = new Image;
	//m_imageData[Up] = new Image;
	//m_imageData[Down] = new Image;

	//m_imageData[Left]->Init("Image/BattleCity/Player/Player.bmp",)
	//m_imageData[Right]->Init;
	//m_imageData[Up]->Init;
	//m_imageData[Down]->Init;

	m_ImageData = ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256,false,RGB(255,0,255));

	m_pos.x = WIN_SIZE_X / 2;
	m_pos.y = WIN_SIZE_Y / 2;

	m_moveDir = MoveDir::Up;
	m_Barrelend.x = m_pos.x;
	m_Barrelend.y = m_pos.y - 32;

	m_bodySize = 64;

	m_moveSpeed = 10;
=======
	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255,0,255));
	//m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");

	//m_pos.x = WIN_SIZE_X / 2;
	//m_pos.y = WIN_SIZE_Y / 2;

	//m_bodySize = 64;

	//m_moveSpeed = 1;
	//m_moveDir = MoveDir::Up;

	//m_Barrelend.x = m_pos.x;
	//m_Barrelend.y = m_pos.y - 32;

	//m_frameX = (int)m_moveDir * 2;;
	//m_frameY = 0;
	//m_maxFrameX = (int)m_moveDir * 2 + 1;;
>>>>>>> parent of d368e0e (? ëª¨ ë§¤ë‹ˆ?€ ì¶”ê?, ? ëª¨ ì¶”ê?, ?±í¬?ì„œ ë°œì‚¬?˜ê²Œ ???¤ì •)

	return S_OK;
}

void PlayerTank::KeyUpdate()
{
#pragma region ÀÔ·ÂºÎ

<<<<<<< HEAD
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
=======
	//if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)))
	//{
	//	m_moveDir = MoveDir::Left;
	//	mb_Move = true;
	//}
	//else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)))
	//{
	//	m_moveDir = MoveDir::Right;
	//	mb_Move = true;
	//}
	//else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_UP)))
	//{
	//	m_moveDir = MoveDir::Up;
	//	mb_Move = true;
	//}
	//else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)))
	//{
	//	m_moveDir = MoveDir::Down;
	//	mb_Move = true;
	//}
	//else
	//{
	//	mb_Move = false;
	//}
>>>>>>> parent of d368e0e (? ëª¨ ë§¤ë‹ˆ?€ ì¶”ê?, ? ëª¨ ì¶”ê?, ?±í¬?ì„œ ë°œì‚¬?˜ê²Œ ???¤ì •)

#pragma endregion
}

void PlayerTank::Render(HDC hdc)
{
	Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);
}
