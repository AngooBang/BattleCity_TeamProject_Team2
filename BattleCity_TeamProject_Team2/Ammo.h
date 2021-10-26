#pragma once
#include "GameObject.h"

class Tank;
class Image;
class TileMap;
class EnemyTank;
class EnemyManager;
class Ammo : public GameObject
{
private:
	LPKILL_COUNT m_killCount = nullptr;

	Image* m_boomImg = nullptr;
	Image* m_img = nullptr;
	MoveDir m_moveDir = MoveDir::End;

	GameObject* m_owner = nullptr;

	EnemyManager* m_enemyMgr = nullptr;
	//vector<EnemyTank*> m_vecEnemys;

	TileMap* m_tileMap = nullptr;

	Tank* m_playerTank = nullptr;


	RECT m_tempRC = {};

	bool mb_isAlive = false;

	bool* mb_isGameOver = nullptr;

	float m_movePosX[4] = { 0, -1,0,1 };
	float m_movePosY[4] = { -1, 0 ,1, 0 };


	int m_frameX = 0;
	int m_frameY = 0;
	int m_maxFrameX = 0;
	float m_elapsedCount = 0.0f;
	float m_totElapsedCount = 0.0f;

public:
	virtual ~Ammo() {}
	HRESULT Init(POINTFLOAT Barrelend, MoveDir moveDir, int ammoSpeed, Image* m_AmmoImage);
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetShape();

	void PlayerAmmoCollider();
	void EnemyAmmoCollider();

	void EnemyCollider();
	void TileCollider();

	inline bool GetIsAlive() { return this->mb_isAlive; }
	inline void SetIsAlive(bool isAlive) { this->mb_isAlive = isAlive; }

	inline float GetTotElapsedCount() { return this->m_totElapsedCount; }

	inline void SetOwner(GameObject* owner) { this->m_owner = owner; }
	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	//inline void SetVecEnemys(vector<EnemyTank*> vecEnemys) { this->m_vecEnemys = vecEnemys; }
	inline void SetEnemyMgr(EnemyManager* enemyMgr) { this->m_enemyMgr = enemyMgr; }

	inline void SetIsGameOver(bool* isGameOver) { this->mb_isGameOver = isGameOver; }

	inline void SetPlayerTank(Tank* playerTank) { this->m_playerTank = playerTank; }



};