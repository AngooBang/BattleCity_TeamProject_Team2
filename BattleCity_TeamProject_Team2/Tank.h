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
	Image* m_img;

	TileMap* m_tileMap;


	int m_frameX;
	int m_maxFrameX;

	int m_frameY;

	int m_elapsedCount;

	RECT m_tempRC;

	POINTFLOAT m_Barrelend;
	int m_HP;
	int m_ammoSpeed;

	bool mb_isAlive;
	bool mb_Move;
	bool mb_isFire;


	bool m_isCollide[MoveDir::End];
		
	MoveDir m_moveDir;

	//RECT m_tileMapShape;
	
	int m_BarrelPosX[4] = { -32,32,0,0 };
	int m_BarrelPosY[4] = { 0,0,-32,32 };

	float m_movePosX[4] = { 0, -1,0,1 };
	float m_movePosY[4] = { -1, 0 ,1, 0 };

	AmmoManager* m_ammoMgr;

public:
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

	//inline void SetTileMapShape(RECT shape) { this->m_tileMapShape = shape; }
	//inline RECT GetTileMapShape() { return this->m_tileMapShape; }

	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	void CheckCollisionDir(RECT a, RECT b);

	inline bool GetisFire() { return mb_isFire; }
	inline void SetisFire(bool isFire) { this->mb_isFire = isFire; }

	inline POINTFLOAT GetPos() { return m_pos; }
	inline POINTFLOAT GetBarrelend() { return m_Barrelend; }
	inline MoveDir GetmoveDir() { return m_moveDir; }
	inline int GetammoSpeed() { return m_ammoSpeed; }

	inline void SetAmmoMgr(AmmoManager* ammoMgr) { this->m_ammoMgr = ammoMgr; }

	inline bool GetAlive() { return mb_isAlive; }
	inline void SetAlive(bool isAlive) { this->mb_isAlive = isAlive; }
};
