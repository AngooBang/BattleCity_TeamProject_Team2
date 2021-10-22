#pragma once
#include "Config.h"
#include "GameObject.h"
#include "TileMap.h"

//typedef TILE_INFO(*Temp)/*[TILE_COUNT_Y]*/[13];

class Tank;
class TileMap;
class EnemyTank;
class AmmoManager;
class EnemyManager : public GameObject
{
private:
	vector<EnemyTank*> vecEnemyTank;
	vector<EnemyTank*>::iterator vecEnemyTankIter;

	// 탱크 테스트용
	Tank* m_player;
	RECT m_tempRect;

	//
	AmmoManager* m_ammoMgr;

	//RECT m_mapShape;
	TileMap* m_tileMap;
	//TILE_INFO *map;
	//Temp p;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AddEnemy(EnemyTank* EnemyTank, POINTFLOAT pos);

	bool isCollisionPlayer(vector<EnemyTank*>::iterator EnemyTankIter);
	inline void SetPlayerTank(Tank* playerTank) { this->m_player = playerTank; }

	inline vector<EnemyTank*> GetVecEnemys() { return vecEnemyTank; }

	inline void SetAmmoMgr(AmmoManager* ammoMgr) { this->m_ammoMgr = ammoMgr; }

	
};
