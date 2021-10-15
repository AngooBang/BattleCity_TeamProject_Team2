#pragma once
#include "Config.h"
#include "GameObject.h"
#include "TileMap.h"

typedef TILE_INFO(*Temp)/*[TILE_COUNT_Y]*/[13];

class TileMap;
class EnemyTank;
class EnemyManager : public GameObject
{
private:
	vector<EnemyTank*> vecEnemyTank;
	vector<EnemyTank*>::iterator vecEnemyTankIter;

	//RECT m_mapShape;
	TileMap* m_tileMap;
	//TILE_INFO *map;
	//Temp p;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AddEnemy(EnemyTank* EnemyTank, POINTFLOAT pos);

	void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	bool CollisionWithTile();
};
