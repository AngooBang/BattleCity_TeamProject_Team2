#pragma once
#include "GameEntity.h"

class Image;
class UIManager;
class TileMap;
class Image;
class EnemyTank;
class PlayerTank;
class GameScene : public GameEntity
{
private:
	Image* m_backGround;

	UIManager* m_uiManager;

	PlayerTank* m_player;
	EnemyTank* m_enemyTank;

	TileMap* m_tileMap;


public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

