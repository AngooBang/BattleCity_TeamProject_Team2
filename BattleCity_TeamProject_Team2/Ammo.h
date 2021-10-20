#pragma once
#include "GameObject.h"

class Tank;
class Image;
class TileMap;
class Ammo : public GameObject
{
	Image* m_img;
	MoveDir m_moveDir;

	GameObject* m_owner;

	TileMap* m_tileMap;

	RECT m_tempRC;

	bool m_isAlive;

	float m_movePosX[4] = { 0, -1,0,1 };
	float m_movePosY[4] = { -1, 0 ,1, 0 };

	Tank* m_playerTank;

public:
	HRESULT Init(POINTFLOAT Barrelend, MoveDir moveDir, int ammoSpeed, Image* m_AmmoImage);
	void Update();
	void Render(HDC hdc);
	void Relese();

	void SetShape();

	void PlayerAmmoCollider();
	void EnemyAmmoCollider();

	void TileCollider();

	inline void SetOwner(GameObject* owner) { this->m_owner = owner; }
	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	inline void SetPlayerTank(Tank* playerTank) { this->m_playerTank = playerTank; }


};