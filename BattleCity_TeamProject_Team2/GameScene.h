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
	Image* m_backGround = nullptr;

	Image* m_gameOver = nullptr;

	POINTFLOAT m_gameOverPos{};

	TileMap* m_tileMap = nullptr;

	UIManager* m_uiManager = nullptr;

	AmmoManager* m_ammoMgr = nullptr;

	Tank* m_player = nullptr;

	EnemyManager* m_enemyMgr = nullptr;

	ItemManager* m_itemMgr = nullptr;

	bool mb_isGameOver{};

	bool mb_isTimeStop{};

	float m_enemySpawnPlaceX = 0.0f;
	float m_spawnPlaceX1 = 0.0f;
	float m_spawnPlaceX2 = 0.0f;
	float m_spawnPlaceX3 = 0.0f;
	float m_spawnPlaceY = 0.0f;

	int m_enemyNumCount = 0;
	int m_enemyTotNum = 0;

	float m_elapsedTime2 = 0.0f;
	float m_elapsedTime = 0.0f;
	float m_goElapsedTime = 0.0f;

	float m_fireTime = 0.0f;
	float m_itemTime = 0.0f;

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

