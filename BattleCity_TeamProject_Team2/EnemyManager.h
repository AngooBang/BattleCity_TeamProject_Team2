#pragma once
#include "Config.h"
#include "GameObject.h"

class EnemyTank;
class EnemyManager : public GameObject
{
private:
	vector<EnemyTank*> vecEnemyTank;
	vector<EnemyTank*>::iterator vecEnemyTankIter;

	RECT m_tileMapShape;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	inline void SetTileMapShape(RECT shape) { this->m_tileMapShape = shape; }
	inline RECT GetTileMapShape() { return this->m_tileMapShape; }

	void AddEnemy(EnemyTank* EnemyTank, POINTFLOAT pos);
};

