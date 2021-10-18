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

void EnemyManager::AddEnemy(EnemyTank* enemyTank, POINTFLOAT pos)
{
    enemyTank->Init(pos, this);
    vecEnemyTank.push_back(enemyTank);
}

bool EnemyManager::CollisionWithTile()
{
    m_tileMap->GetShape();
    for (vecEnemyTankIter = vecEnemyTank.begin(); vecEnemyTankIter != vecEnemyTank.end();
        ++vecEnemyTankIter)
    {
        if (CheckInRect((*vecEnemyTankIter)->GetShape(), m_tileMap->GetShape() ) )
        {

        }
    }
    /*p = m_tileMap->GetMapTileInfo();
    cout << p[0][0].rc.left << endl;*/
    /*cout << map[0][0].rc.left << endl;
    cout << map[0][0].rc.right << endl;*/

    return true;
}
