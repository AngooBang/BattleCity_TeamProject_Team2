#pragma once
#include "GameEntity.h"
class GameScene : public GameEntity
{
private:

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

