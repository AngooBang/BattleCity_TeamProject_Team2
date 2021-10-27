#pragma once
#include "GameEntity.h"

class Image;
class GameOverScene : public GameEntity
{
private:
	Image* m_gameOver = nullptr;
	Image* m_backGround = nullptr;
	float m_elapsedTime{};

public:
	virtual ~GameOverScene() {}
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

};

