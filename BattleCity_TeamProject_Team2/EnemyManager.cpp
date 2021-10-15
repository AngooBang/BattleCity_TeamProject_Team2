#include "EnemyManager.h"
#include "EnemyTank.h"
#include "TileMap.h"

HRESULT EnemyManager::Init()
{

    return S_OK;
}

void EnemyManager::Update()
{
    for (vecEnemyTankIter = vecEnemyTank.begin(); vecEnemyTankIter != vecEnemyTank.end(); 
        ++vecEnemyTankIter)
    {
        (*vecEnemyTankIter)->Update();
    }
}

void EnemyManager::Render(HDC hdc)
{
    for (vecEnemyTankIter = vecEnemyTank.begin(); vecEnemyTankIter != vecEnemyTank.end();
        ++vecEnemyTankIter)
    {
        (*vecEnemyTankIter)->Render(hdc);
    }
}

void EnemyManager::Release()
{
    for (vecEnemyTankIter = vecEnemyTank.begin(); vecEnemyTankIter != vecEnemyTank.end();
        ++vecEnemyTankIter)
    {
        SAFE_RELEASE((*vecEnemyTankIter));
    }
}

void EnemyManager::AddEnemy(EnemyTank* EnemyTank, POINTFLOAT pos)
{
    EnemyTank->Init(pos);
    vecEnemyTank.push_back(EnemyTank);
}

bool EnemyManager::CollisionWithTile()
{
    /*p = m_tileMap->GetMapTileInfo();
    cout << p[0][0].rc.left << endl;*/
    /*cout << map[0][0].rc.left << endl;
    cout << map[0][0].rc.right << endl;*/

    return true;
}
