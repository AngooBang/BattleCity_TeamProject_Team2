#pragma once
#include "Config.h"
#include "GameObject.h"

class EnemyTank;
class EnemyManager : public GameObject
{
private:
	vector<EnemyTank*> vecEnemyTank;
	vector<EnemyTank*>::iterator vecEnemyTankIter;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AddEnemy(EnemyTank* EnemyTank, POINTFLOAT pos);
};

