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

	int m_elapsedCount = 0;
	int m_frameX;
	int m_maxFrameX;
	int m_frameY;

	POINTFLOAT m_Barrelend;
	bool mb_isAlive;
	bool mb_Move;
	
	Image* m_ImageData;

	MoveDir m_moveDir;
	
	int m_BarrelPosX[4] = { 0,-32,0,32 };
	int m_BarrelPosY[4] = { -32,0,32,0 };

	//float m_movePosX[4] = { 0, -1,0,1 };
	//float m_movePosY[4] = { -1, 0 ,1, 0 };

public:
	virtual HRESULT Init();
	virtual void KeyUpdate() {};
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetBarrel(int x, int y);
	void SetPosMove(int x, int y);
	void SetMoveDir(MoveDir moveDir);
	void SetImage();

};

