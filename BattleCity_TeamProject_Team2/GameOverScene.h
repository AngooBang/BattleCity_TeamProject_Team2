#pragma once
#include "GameEntity.h"

class Image;
class GameOverScene : public GameEntity
{
private:
	Image* m_gameOver;
	Image* m_backGround;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

