#pragma once
#include "GameObject.h"

#define MOVE_CORRECTION_VALUE 10

class Image;
class TileMap;
class Ammo;
class AmmoManager;
class Tank : public GameObject
{
protected:
	//const POINTFLOAT DirLeft{ -1, 0 };
	//const POINTFLOAT DirRight{ 1, 0 };
	//const POINTFLOAT DirTop{ 0, -1 };
	//const POINTFLOAT DirBottom{ 0, 1 };

	//POINTFLOAT mDir;
	Image* m_img = nullptr;
	Image* m_shieldImg = nullptr;
	Image* m_boomImg = nullptr;

	TileMap* m_tileMap = nullptr;

	int m_frameX = 0;
	int m_maxFrameX = 0;

	int m_shieldframeX = 0;

	int m_frameY = 0;

	int m_elapsedCount = 0;

	RECT m_tempRC = {};

	POINTFLOAT m_Barrelend = {};
	int m_tempHP = 0;
	int m_HP = 0;
	float m_ammoSpeed = 0.0f;

	bool mb_isAlive = false;
	bool mb_Move = false;
	bool mb_isSpawn = false;
	bool mb_isFire = false;
	bool mb_isShield = false;
	bool mb_isDead = false;

	float m_spawnTimer = 0.0f;
	float m_shieldTimer = 0.0f;

	bool m_isCollide[MoveDir::End];
		
	MoveDir m_moveDir = {};
	
	int m_BarrelPosX[4] = { -32,32,0,0 };
	int m_BarrelPosY[4] = { 0,0,-32,32 };

	float m_movePosX[4] = { 0, -1,0,1 };
	float m_movePosY[4] = { -1, 0 ,1, 0 };

	AmmoManager* m_ammoMgr = nullptr;

public:
	virtual ~Tank() {}
	virtual HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetBarrel(int x, int y);
	void SetImage();

	void SetPosMove(int x, int y);
	void SetMoveDir(MoveDir moveDir);

	void SetShape();

	void MoveCorrection();

	void SpawnPlayer();
	void ShieldPlayer();
	void UpgradeTank();

	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	void CheckCollisionDir(RECT a, RECT b);

	inline bool GetisFire() { return mb_isFire; }
	inline void SetisFire(bool isFire) { this->mb_isFire = isFire; }

	inline POINTFLOAT GetPos() { return m_pos; }
	inline POINTFLOAT GetBarrelend() { return m_Barrelend; }
	inline MoveDir GetmoveDir() { return m_moveDir; }
	inline float GetammoSpeed() { return m_ammoSpeed; }

	inline void SetAmmoMgr(AmmoManager* ammoMgr) { this->m_ammoMgr = ammoMgr; }

	inline bool GetAlive() { return mb_isAlive; }
	inline void SetAlive(bool isAlive) { this->mb_isAlive = isAlive; }

	inline int GetHP() { return m_HP; }
	inline void SetHP(int hp) { this->m_HP += hp; }

	inline int GetFrameY() { return m_frameY; }
};
