#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class EnemyTank : public GameEntity
{
private:
	POINTFLOAT m_pos;
	POINTFLOAT m_bodySize;
	RECT m_shape;
	float m_moveSpeed;
	MoveDir m_moveDir;

	int m_elapsedCount;
	int m_moveDelay;

	int m_elapsedCount2;
	int m_imgDelay;
	int m_frameX;
	int m_maxFrameX;
	int m_frameY;

	Image* m_backGround;
	Image* m_img;
	
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void AutoMove();
};

