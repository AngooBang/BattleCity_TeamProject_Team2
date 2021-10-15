#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class EnemyTank : public GameObject
{
protected:
	MoveDir m_moveDir;

	int m_elapsedCount = 0;
	int m_moveDelay = 70;

	int m_enemyFrame[MoveDir::End];

	int m_imgDelay = 5;
	int m_frameX;
	int m_maxFrameX;
	int m_frameY;

	Image* m_backGround;
	
	RECT m_mapShape;

public:
	virtual HRESULT Init(POINTFLOAT pos);
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	void AutoMove();

	EnemyTank(/*int a, RECT b*/) { /*m_mapBodySize = a; m_mapShape = b;*/ }
	~EnemyTank() {};
};

