#pragma once
#include "GameEntity.h"

class EnemyTank;
class Image;
class UIManager;
class TileMap;
class EnemyManager;
class Tank;
class AmmoManager;
class ItemManager;
class GameScene : public GameEntity
{
private:

	Image* m_backGround;

	Image* m_gameOver;

	POINTFLOAT m_gameOverPos;

	TileMap* m_tileMap;

	UIManager* m_uiManager;

	AmmoManager* m_ammoMgr;

	Tank* m_player;

	EnemyManager* m_enemyMgr;

	ItemManager* m_itemMgr;

	bool mb_isGameOver;

	bool mb_isTimeStop;


	float m_enemySpawnPlaceX = 0;
	float m_spawnPlaceX1 = 0;
	float m_spawnPlaceX2 = 0;
	float m_spawnPlaceX3 = 0;
	float m_spawnPlaceY = 0;

	int m_enemyNumCount = 0;
	int m_enemyTotNum = 0;

	float m_elapsedTime = 0;
	float m_goElapsedTime;

	float m_fireTime = 0;

public:
	virtual ~GameScene() {}
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();

	
	inline Tank* GetPlayer() { return this->m_player; }

	inline EnemyManager* GetEnemyMgr() { return this->m_enemyMgr; }

	inline TileMap* GetTileMap() { return this->m_tileMap; }

	inline void SetIsTimeStop(bool isTimeStop) { this->mb_isTimeStop = isTimeStop; }
	inline bool GetIsTimeStop() { return this->mb_isTimeStop; }

	void SpawnEnemy();
};

