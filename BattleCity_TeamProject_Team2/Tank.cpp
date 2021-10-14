#include "Tank.h"

HRESULT Tank::Init()
{
	return S_OK;
}

void Tank::Update()
{
#pragma region 입력부
	KeyUpdate();
	//
	//	if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)))
	//	{
	//		m_moveDir = MoveDir::Left;
	//	}
	//	else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)))
	//	{
	//		m_moveDir = MoveDir::Right;
	//	}
	//	else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_UP)))
	//	{
	//		m_moveDir = MoveDir::Up;
	//	}
	//	else if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)))
	//	{
	//		m_moveDir = MoveDir::Down;
	//	}
#pragma endregion

// 충돌처리에 대한 bool 변수 값 받아야함.

#pragma region 이동값 처리부
	
	if (mb_Move)
	{
		SetMove(m_movePosX[(int)m_moveDir], m_movePosY[(int)m_moveDir]);
	}

	//if (iscollide == false)
	//{
	//pos.x += mDir.x * moveSpeed;
	//pos.y += mDir.y * moveSpeed;
	// 
	//if (m_moveDir == MoveDir::Left)
	//{
	//	pos.x += -moveSpeed;
	//}
	//else if (m_moveDir == MoveDir::Right)
	//{
	//	pos.x += moveSpeed;
	//}
	//else if (m_moveDir == MoveDir::Up)
	//{
	//	pos.y += -moveSpeed;
	//}
	//else if (m_moveDir == MoveDir::Down)
	//{
	//	pos.y += moveSpeed;
	//}
	//}
#pragma endregion

#pragma region 이미지 처리부

	SetImage();

#pragma endregion
	SetBarrel(m_BarrelPosX[(int)m_moveDir], m_BarrelPosY[(int)m_moveDir]);

#pragma endregion


#pragma region 포신방향 설정부
		
	m_shape.left = m_pos.x - 32;
	m_shape.right = m_pos.x + 32;
	m_shape.top = m_pos.y - 32;
	m_shape.bottom = m_pos.y + 32;
}

void Tank::Render(HDC hdc)
{
}

void Tank::Release()
{
}

void Tank::SetBarrel(int x, int y)
{
	m_Barrelend.x = m_pos.x + x;
	m_Barrelend.y = m_pos.y + y;
}

void Tank::SetMove(int x, int y)
{
	m_pos.x += x * m_moveSpeed;
	m_pos.y += y * m_moveSpeed;
}

void Tank::SetImage()
{
	

}
