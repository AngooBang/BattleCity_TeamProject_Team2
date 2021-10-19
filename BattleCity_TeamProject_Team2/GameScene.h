#pragma once
#include "GameEntity.h"

class Image;
class UIManager;
class TileMap;
class EnemyManager;
class Tank;
<<<<<<< HEAD
class AmmoManager;
=======
>>>>>>> 320c4afa4d706ea9bed618bb2546e8d1fce8ca12
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

