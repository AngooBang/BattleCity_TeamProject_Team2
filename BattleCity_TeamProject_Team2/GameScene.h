#pragma once
#include "GameEntity.h"

class EnemyTank;
class GameScene : public GameEntity
{
private:
	EnemyTank* enemyTank;


public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

