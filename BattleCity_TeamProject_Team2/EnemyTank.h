#pragma once
#include "Config.h"
#include "GameObject.h"

#define MOVE_CORRECTION_VALUE 10

enum class EnemyStatus {Create, Alive, Dead, End};

class Image;
class TileMap;
class EnemyManager;
class EnemyTank : public GameObject
{
protected:
	MoveDir m_moveDir = MoveDir::Down;

	Image* m_img;
	EnemyManager* m_manager;

	int m_elapsedCount = 0;
	int m_moveDelay = 70;

	int m_enemyFrame[MoveDir::End];

	int m_imgDelay = 5;
	int m_frameX;
	int m_frameCount = 1;
	int m_maxFrameX;
	int m_frameY;

	Image* m_backGround;

	float totElapsedCount = 0.0f;
	EnemyStatus m_enemyStatus;

	MoveDir m_beforeMoveDir;
	bool mb_dirCheck[4];

	TileMap* m_tileMap;

	RECT m_tempRC;
	bool m_isCollide[MoveDir::End];

public:
	virtual HRESULT Init(POINTFLOAT pos, EnemyManager* manager);
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release();

	void AutoMove();
	void RandomDirChange();

	bool IsCollisionMap();
	bool IsCollisionTile();
	void MoveCorrection();

	EnemyTank() {}
	~EnemyTank() {};
};

