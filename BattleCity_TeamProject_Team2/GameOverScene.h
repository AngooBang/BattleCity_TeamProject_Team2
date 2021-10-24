#pragma once
#include "GameEntity.h"

class Image;
class GameOverScene : public GameEntity
{
private:
	Image* m_gameOver;
	Image* m_backGround;
	Image* m_img = nullptr;
	float m_elapsedTime = 0;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	GameOverScene() {};
	virtual ~GameOverScene() {};
};

