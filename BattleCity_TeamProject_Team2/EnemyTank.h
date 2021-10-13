#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class EnemyTank : public GameObject
{
private:
	MoveDir m_moveDir;

	int m_elapsedCount;
	int m_moveDelay;

	int m_enemyFrame[MoveDir::End];

	int m_imgDelay;
	int m_frameX;
	int m_maxFrameX;
	int m_frameY;

	Image* m_backGround;
	
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void AutoMove();
};

