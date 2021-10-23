#pragma once
#include "GameEntity.h"

class Image;
class TitleScene : public GameEntity
{
private:
	Image* m_title;
	Image* m_enemyType;
	Image* m_backGround2;

	int m_moveSpeed = 5;

	POINTFLOAT m_pos;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AutoMove();
};

