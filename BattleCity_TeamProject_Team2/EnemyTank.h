#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class EnemyManager;
class EnemyTank : public GameObject
{
protected:
	MoveDir m_moveDir;

	Image* m_img;
	EnemyManager* m_manager;

	int m_elapsedCount = 0;
	int m_moveDelay = 70;

	int m_enemyFrame[MoveDir::End];

	int m_imgDelay = 5;
	int m_frameX;
	int m_maxFrameX;
	int m_frameY;

	Image* m_backGround;
	
public:
	virtual HRESULT Init(POINTFLOAT pos, EnemyManager* manager);
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release();

	void AutoMove();
};

