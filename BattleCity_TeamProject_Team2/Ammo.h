#pragma once
#include "GameObject.h"
#include "Config.h"
#include "Image.h"

class Collider;
class Ammo : public GameObject
{
	MoveDir m_moveDir;

	float m_movePosX[4] = { 0, -1,0,1 };
	float m_movePosY[4] = { -1, 0 ,1, 0 };

public:
	HRESULT Init(POINTFLOAT Barrelend, MoveDir moveDir, int ammoSpeed, Image* m_AmmoImage[]);
	void Update();
	void Render(HDC hdc);
	void Relese();
};