#pragma once
#include "Config.h"
#include "GameObject.h"

class Ammo;
class Tank;
class AmmoManager : public GameObject
{
private:
	Image* m_AmmoImage[4];

	vector<Ammo*> m_vecAmmo;
	vector<Ammo*>::iterator m_vecAmmoIter;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AddAmmo(Ammo* Ammo, Tank* tank);
};