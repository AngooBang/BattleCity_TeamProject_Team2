#pragma once
#include "GameObject.h"
#include "Config.h"
#include "Image.h"

class Tank : public GameObject
{
protected:
	//const POINTFLOAT DirLeft{ -1, 0 };
	//const POINTFLOAT DirRight{ 1, 0 };
	//const POINTFLOAT DirTop{ 0, -1 };
	//const POINTFLOAT DirBottom{ 0, 1 };

	//POINTFLOAT mDir;

	POINTFLOAT m_Barrelend;
	bool mb_isAlive;
	bool mb_Move;
		
	MoveDir m_moveDir;
	
	int m_BarrelPosX[4] = { -32,32,0,0 };
	int m_BarrelPosY[4] = { 0,0,-32,32 };

	float m_movePosX[4] = { -1, 1,0,0 };
	float m_movePosY[4] = { 0,0 , -1, 1 };

public:
	virtual HRESULT Init();
	virtual void KeyUpdate() {};
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetBarrel(int x, int y);
	void SetMove(int x, int y);
	void SetImage();

};

