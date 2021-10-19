#pragma once
#include "GameEntity.h"

class Image;
class UIManager;
class TileMap;
class EnemyManager;
class Tank;
class AmmoManager;
class GameScene : public GameEntity
{
private:
	Image* m_backGround;

	TileMap* m_tileMap;

	UIManager* m_uiManager;

	Tank* m_player;

	EnemyManager* m_enemyMgr;

	AmmoManager* m_ammoMgr;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

