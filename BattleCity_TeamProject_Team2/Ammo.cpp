#include "Ammo.h"

HRESULT Ammo::Init(POINTFLOAT Barrelend, MoveDir moveDir, int ammoSpeed, Image* m_AmmoImage[])
{
	m_img = m_AmmoImage[(int)moveDir];

	m_moveDir = moveDir;
	m_moveSpeed = ammoSpeed;
	m_pos.x = Barrelend.x;
	m_pos.y = Barrelend.y;
	
	m_shape.left = m_pos.x - 5;
	m_shape.right = m_pos.x + 5;
	m_shape.top = m_pos.y - 5;
	m_shape.bottom = m_pos.y + 10;

	return S_OK;
}

void Ammo::Update()
{
	m_pos.x += m_movePosX[(int)m_moveDir] * m_moveSpeed;
	m_pos.y += m_movePosY[(int)m_moveDir] * m_moveSpeed;
}

void Ammo::Render(HDC hdc)
{
	//Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);
	m_img->Render(hdc, m_pos.x, m_pos.y, 0, 0, 2.0f);
}

void Ammo::Relese()
{
	if (m_img)  SAFE_RELEASE(m_img);
}
