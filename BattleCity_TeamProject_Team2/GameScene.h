#pragma once
#include "GameEntity.h"

class Image;
class UIManager;
class TileMap;

class Image;

class EnemyTank;
class GameScene : public GameEntity
{
private:
	Image* m_backGround;
	EnemyTank* enemyTank;


	TileMap* m_tileMap;
	UIManager* m_uiManager;
public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

