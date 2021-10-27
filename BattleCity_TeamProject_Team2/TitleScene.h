#pragma once
#include "GameEntity.h"

class Image;
class TitleScene : public GameEntity
{
private:
	Image* m_title = nullptr;
	Image* m_enemyType = nullptr;
	Image* m_backGround2 = nullptr;

	int m_moveSpeed = 5;

	POINTFLOAT m_pos{};

public:
	virtual ~TitleScene() {}
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AutoMove();
};

