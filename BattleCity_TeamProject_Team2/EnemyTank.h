#pragma once
#include "Config.h"
#include "GameObject.h"

#define MOVE_CORRECTION_VALUE 10

enum class EnemyStatus {Create, Alive, Dead, End};

class Image;
class TileMap;
class EnemyManager;
class GameScene;
class EnemyTank : public GameObject
{
protected:
	Image* m_backGround = nullptr;
	Image* m_img = nullptr;
	Image* m_boomImage = nullptr;

	GameScene* m_gameScene = nullptr;

	MoveDir m_moveDir = MoveDir::Down;
	int m_enemyFrame[MoveDir::End] = {0};
	
	int m_elapsedCount = 0;
	int m_moveDelay = 70;

	int m_frameX = 0;
	int m_frameCount = 1;
	int m_maxFrameX = 0;
	int m_frameY = 0;

	float totElapsedCount = 0.0f;
	EnemyStatus m_enemyStatus = EnemyStatus::End;

	MoveDir m_beforeMoveDir = MoveDir::End;
	bool mb_dirCheck[4] = {0};

	TileMap* m_tileMap = nullptr;

	RECT m_tempRC = {};
	bool m_isCollide[MoveDir::End];

	int m_HP = 0;
	float m_ammoSpeed = 0.0f;

	bool mb_isAlive = true;
	bool mb_isFire = true;
	float m_fireElapsedCount = 0.0f;

	EnemyType m_enemyTankType = EnemyType::End;

	bool mb_isReady = true;
	float m_boomElapsedCount = 0.0f;
	bool m_renderScore = false;
	bool m_hitByGranade = false;
	float m_scale = 0.0f;

public:
	virtual ~EnemyTank() {}
	virtual HRESULT Init(POINTFLOAT pos);
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release();

	void AutoMove();
	void RandomDirChange();
	void TimeDirChange();

	bool IsCollisionMap();
	bool IsCollisionMap(MoveDir& dir);
	bool IsCollisionTile();
	void MoveCorrection();


	void SetGameScene(GameScene* gameScene) { this->m_gameScene = gameScene; }


	inline void SetIsAlive(bool isAlive) { this->mb_isAlive = isAlive; }
	inline bool GetIsAlive() { return mb_isAlive; }

	inline bool GetisFire() { return mb_isFire; }
	inline void SetisFire(bool isFire) { this->mb_isFire = isFire; }

	inline MoveDir GetmoveDir() { return m_moveDir; }
	inline void SetmoveDir(MoveDir moveDir) { this->m_moveDir = moveDir; }

	inline float GetammoSpeed() { return m_ammoSpeed; }

	inline int GetHP() { return m_HP; }
	inline void SetHP(int num) { this->m_HP += num; }

	inline void SetEnemyStatus(EnemyStatus enemyStatus) { this->m_enemyStatus = enemyStatus; }
	inline EnemyStatus GetEnemyStatus() { return m_enemyStatus; }

	inline void SetFrameY(int frameY) { this->m_frameY = frameY; }

	inline void SetEnemyType(EnemyType enemyType) { this->m_enemyTankType = enemyType; }
	inline EnemyType GetEnemyType() { return m_enemyTankType; }

	inline int GetFrameX() { return m_frameX; }
	inline void SetFrameX(int frameX) { this->m_frameX = frameX; }

	inline void SetMaxFrameX(int maxFrameX) { this->m_maxFrameX = maxFrameX; }

	inline bool* GetDirCehck() { return mb_dirCheck; }

	inline void SetBeforeMoveDir(MoveDir beforeMoveDir) { this->m_beforeMoveDir = beforeMoveDir; }

	inline void SetMoveSpeed(float moveSpeed) { this->m_moveSpeed = moveSpeed; }
	inline float GetMoveSpeed() { return m_moveSpeed; }

	inline void SetHitByGranade(bool hitByGranade) { this->m_hitByGranade = hitByGranade; }

};

