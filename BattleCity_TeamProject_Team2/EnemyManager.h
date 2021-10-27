#pragma once
#include "Config.h"
#include "GameObject.h"
#include "TileMap.h"

class Tank;
class TileMap;
class EnemyTank;
class AmmoManager;
class GameScene;
class EnemyManager : public GameObject
{
private:
	vector<EnemyTank*> vecEnemyTank{};

	// 탱크 테스트용
	Tank* m_player = nullptr;
	RECT m_tempRect = {};

	GameScene* m_gameScene = nullptr;
	AmmoManager* m_ammoMgr = nullptr;

	TileMap* m_tileMap = nullptr;

public:
	virtual ~EnemyManager() {}
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetGameScene(GameScene* gameScene) { this->m_gameScene = gameScene; }

	void AddEnemy(EnemyTank* EnemyTank, POINTFLOAT pos);

	inline void SetTileMap(TileMap* tileMap) { this->m_tileMap = tileMap; }

	bool isCollisionPlayer(vector<EnemyTank*>::iterator EnemyTankIter);
	inline void SetPlayerTank(Tank* playerTank) { this->m_player = playerTank; }

	inline vector<EnemyTank*>& GetVecEnemys() { return vecEnemyTank; }

	inline void SetAmmoMgr(AmmoManager* ammoMgr) { this->m_ammoMgr = ammoMgr; }

	void CollisionEnemyTank(int i, int j);
};
