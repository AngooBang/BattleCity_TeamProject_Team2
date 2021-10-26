#pragma once
#include "Config.h"
#include "GameObject.h"

class Ammo;
class Tank;
class EnemyTank;
class TileMap;
class EnemyManager;
class AmmoManager : public GameObject
{
private:
	Image* m_AmmoImage[MoveDir::End];


	vector<Ammo*> m_vecAmmo;
	vector<Ammo*>::iterator m_vecAmmoIter;

	EnemyManager* m_enemyMgr;

	TileMap* m_tileMap;

	bool* mb_isGameOver;


public:
	virtual ~AmmoManager() {}
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AddAmmo(Ammo* Ammo, Tank* tank);
	void AddAmmo(Ammo* Ammo, EnemyTank* enemyTank, Tank* target);

	void AmmoCollision();

	//inline void SetVecEnemys(vector<EnemyTank*> vecEnemys) { this->m_vecEnemys = vecEnemys; }

	inline void SetEnemyMgr(EnemyManager* enemyMgr) { this->m_enemyMgr = enemyMgr; }

	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	inline void SetIsGameOver(bool* isGameOver) { this->mb_isGameOver = isGameOver; }
	

};