#include "Tank.h"

HRESULT Tank::Init()
{
	return S_OK;
}

void Tank::Update()
{
#pragma region �Էº�
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

// �浹ó���� ���� bool ���� �� �޾ƾ���.

#pragma region �̵��� ó����
	
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

#pragma region �̹��� ó����

	SetImage();

#pragma endregion

#pragma region ���Ź��� ������
		
	SetBarrel(m_BarrelPosX[(int)m_moveDir], m_BarrelPosY[(int)m_moveDir]);

#pragma endregion

	shape.left = pos.x - 32;
	shape.right = pos.x + 32;
	shape.top = pos.y - 32;
	shape.bottom = pos.y + 32;
}

void Tank::Render(HDC hdc)
{
}

void Tank::Release()
{
}

void Tank::SetBarrel(int x, int y)
{
	m_Barrelend.x = pos.x + x;
	m_Barrelend.y = pos.y + y;
}

void Tank::SetMove(int x, int y)
{
	pos.x += x * moveSpeed;
	pos.y += y * moveSpeed;
}

void Tank::SetImage()
{
	

}
