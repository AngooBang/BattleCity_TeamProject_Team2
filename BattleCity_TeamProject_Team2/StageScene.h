#pragma once
#include "GameEntity.h"

class Image;
class StageScene : public GameEntity
{
private:
	Image* m_stageNumber = nullptr;
	Image* m_stage = nullptr;
	Image* m_enemyType = nullptr;
	Image* m_backGround = nullptr;
	Image* m_backGround2 = nullptr;

	int m_stageNr = 0;
	int m_stageNumX[10] = { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };

	int m_stageNumY[10] = { 0,0,0,0,0,1,1,1,1,1 };

	int m_moveSpeed = 15;
	float m_elapsedTime = 0.0f;
	POINTFLOAT m_pos{};
	POINTFLOAT m_pos2{};

public:
	virtual ~StageScene() {}
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AutoMove();
};
