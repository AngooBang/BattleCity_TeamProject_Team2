#pragma once
#include "GameEntity.h"

class UIManager;
class Image;

class EnemyTank;
class GameScene : public GameEntity
{
private:
	Image* m_backGround;
	EnemyTank* enemyTank;


	UIManager* m_uiManager;
public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

