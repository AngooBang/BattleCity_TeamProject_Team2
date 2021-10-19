#pragma once
#include "GameObject.h"

class Image;
class Ammo : public GameObject
{
	Image* m_img;
	MoveDir m_moveDir;

	float m_movePosX[4] = { 0, -1,0,1 };
	float m_movePosY[4] = { -1, 0 ,1, 0 };

public:
	HRESULT Init(POINTFLOAT Barrelend, MoveDir moveDir, int ammoSpeed, Image* m_AmmoImage[]);
	void Update();
	void Render(HDC hdc);
	void Relese();
};