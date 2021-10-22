#pragma once
#include "GameEntity.h"

typedef struct KillCount
{
	int BasicTankNr;
	int SpeedTankNr;
	int PowerTankNr;
	int ArmorTankNr;
}*LPKillCount;

class EnemyTank;
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

	AmmoManager* m_ammoMgr;

	Tank* m_player;

	EnemyManager* m_enemyMgr;

	KillCount m_killCount;

	float m_enemySpawnPlaceX = 0;
	float m_spawnPlaceX1 = 0;
	float m_spawnPlaceX2 = 0;
	float m_spawnPlaceX3 = 0;
	float m_spawnPlaceY = 0;

	int m_enemyNumCount = 0;
	int m_enemyTotNum = 0;
	int m_basicTankNum = 0;
	int m_speedTankNum = 0;
	int m_powerTankNum = 0;
	int m_armorTankNum = 0;

	float m_elapsedTime = 0;

	float m_fireTime = 0;

	vector<EnemyTank*> m_vecEnemyTank;
	vector<EnemyTank*>::iterator m_it;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

