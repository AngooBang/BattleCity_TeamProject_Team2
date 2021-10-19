#pragma once
#include "Config.h"
#include "GameObject.h"

class Ammo;
class Tank;
class EnemyTank;
class TileMap;
class AmmoManager : public GameObject
{
private:
	Image* m_AmmoImage[MoveDir::End];

	vector<Ammo*> m_vecAmmo;
	vector<Ammo*>::iterator m_vecAmmoIter;

	TileMap* m_tileMap;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AddAmmo(Ammo* Ammo, Tank* tank);
	void AddAmmo(Ammo* Ammo, EnemyTank* tank);


	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }
};