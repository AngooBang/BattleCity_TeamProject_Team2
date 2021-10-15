#pragma once
#include "GameObject.h"


class Image;
class TileMap;
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


	POINTFLOAT m_Barrelend;
	bool mb_isAlive;
	bool mb_Move;

	bool m_isCollide[MoveDir::End];
		
	MoveDir m_moveDir;

	//RECT m_tileMapShape;
	
	int m_BarrelPosX[4] = { -32,32,0,0 };
	int m_BarrelPosY[4] = { 0,0,-32,32 };

	float m_movePosX[4] = { -1, 1,0,0 };
	float m_movePosY[4] = { 0,0 , -1, 1 };

public:
	virtual HRESULT Init();
	virtual void KeyUpdate() {};
	void Update();
	void Render(HDC hdc);
	void Release();


	void SetBarrel(int x, int y);
	void SetImage();

	void SetPosMove(int x, int y);
	void SetMoveDir(MoveDir moveDir);

	void SetShape();


	//inline void SetTileMapShape(RECT shape) { this->m_tileMapShape = shape; }
	//inline RECT GetTileMapShape() { return this->m_tileMapShape; }

	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	void CheckCollisionDir(RECT a, RECT b);

};

