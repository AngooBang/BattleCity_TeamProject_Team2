#include "Tank.h"
#include "Ammo.h"
#include "AmmoManager.h"

HRESULT Tank::Init()
{
	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
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
	// 나중에...
	return S_OK;
}

void Tank::Update()
{
#pragma region 입력부

	//if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)))
	//{
	//	SetMoveDir(MoveDir::Left);

	//	if (m_moveDir != MoveDir::Left)
	//	{
	//		m_moveDir = MoveDir::Left;
	//		m_frameX = (int)m_moveDir * 2;
	//		m_maxFrameX = (int)m_moveDir * 2 + 1;
	//	}
	//	mb_Move = true;
	//}
	//else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)))
	//{
	//	SetMoveDir(MoveDir::Right);

	//	if (m_moveDir != MoveDir::Right)
	//	{
	//		m_moveDir = MoveDir::Right;
	//		m_frameX = (int)m_moveDir * 2;
	//		m_maxFrameX = (int)m_moveDir * 2 + 1;
	//	}
	//	mb_Move = true;
	//}
	//else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_UP)))
	//{
	//	SetMoveDir(MoveDir::Up);

	//	if (m_moveDir != MoveDir::Up)
	//	{
	//		m_moveDir = MoveDir::Up;
	//		m_frameX = (int)m_moveDir * 2;
	//		m_maxFrameX = (int)m_moveDir * 2 + 1;
	//	}
	//	mb_Move = true;
	//}
	//else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)))
	//{
	//	SetMoveDir(MoveDir::Down);

	//	if (m_moveDir != MoveDir::Down)
	//	{
	//		m_moveDir = MoveDir::Down;
	//		m_frameX = (int)m_moveDir * 2;
	//		m_maxFrameX = (int)m_moveDir * 2 + 1;
	//	}
	//	mb_Move = true;
	//}
	//else
	//{
	//	mb_Move = false;
	//}


#pragma endregion

#pragma region 이동값 처리부

// 충돌처리에 대한 bool 변수 값 받아야함.

	if (mb_Move)
	{
		SetPosMove(m_movePosX[(int)m_moveDir], m_movePosY[(int)m_moveDir]);
	//}
	//if (iscollide == false)
		//{
		//pos.x += mDir.x * moveSpeed;
		//pos.y += mDir.y * moveSpeed;
		 
		//if (m_moveDir == MoveDir::Left)
		//{
		//	m_pos.x += -m_moveSpeed;
		//}
		//else if (m_moveDir == MoveDir::Right)
		//{
		//	m_pos.x += m_moveSpeed;
		//}
		//else if (m_moveDir == MoveDir::Up)
		//{
		//	m_pos.y += -m_moveSpeed;
		//}
		//else if (m_moveDir == MoveDir::Down)
		//{
		//	m_pos.y += m_moveSpeed;
		//}
	}
#pragma endregion

#pragma region 이미지 처리부

	//SetImage();

	//if (mb_Move)
	//{
	//	++m_elapsedCount;
	//	if (m_elapsedCount % 5 == 0)
	//	{
	//		++m_frameX;
	//		if (m_frameX > m_maxFrameX)
	//		{
	//			m_frameX -= 2;
	//		}
	//		m_elapsedCount = 0;
	//	}
	//}

	//if (mb_Move)
	//{
	//	++m_elapsedCount;
	//	if (m_elapsedCount % 5 == 0)
	//	{
	//		++m_frameX;
	//		if (m_frameX > m_maxFrameX)
	//		{
	//			m_frameX -= 2;
	//		}
	//		m_elapsedCount = 0;
	//	}
	//}

#pragma endregion

#pragma region 포신방향 설정부
		
	SetBarrel(m_BarrelPosX[(int)m_moveDir], m_BarrelPosY[(int)m_moveDir]);

#pragma endregion

#pragma region 총알 발사

	if (mb_isFire)
	{
		
	}

#pragma endregion

	m_shape.left = m_pos.x - 32;
	m_shape.right = m_pos.x + 32;
	m_shape.top = m_pos.y - 32;
	m_shape.bottom = m_pos.y + 32;
}

void Tank::Render(HDC hdc)
{
	Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);

	if (m_img)
		m_img->Render(hdc, m_pos.x, m_pos.y, m_frameX, m_frameY);
}

void Tank::Release()
{
	if (m_img)  SAFE_RELEASE(m_img);
}

void Tank::SetBarrel(int x, int y)
{
	m_Barrelend.x = m_pos.x + x;
	m_Barrelend.y = m_pos.y + y;
}

void Tank::SetPosMove(int x, int y)
{
	m_pos.x += x * m_moveSpeed;
	m_pos.y += y * m_moveSpeed;
}

void Tank::SetMoveDir(MoveDir moveDir)
{
	if (m_moveDir != moveDir)
	{
		m_moveDir = moveDir;
		m_frameX = (int)m_moveDir * 2;
		m_maxFrameX = (int)m_moveDir * 2 + 1;
	}
	mb_Move = true;
}

void Tank::SetImage()
{
	if (mb_Move)
	{
		++m_elapsedCount;
		if (m_elapsedCount % 5 == 0)
		{
			++m_frameX;
			if (m_frameX > m_maxFrameX)
			{
				m_frameX -= 2;
			}
			m_elapsedCount = 0;
		}
	}
}
