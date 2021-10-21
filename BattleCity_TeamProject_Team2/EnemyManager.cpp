#include "EnemyManager.h"
#include "EnemyTank.h"
#include "TileMap.h"
#include "Tank.h"
#include "AmmoManager.h"
#include "Ammo.h"

HRESULT EnemyManager::Init(AmmoManager* ammoMgr)
{
    this->m_ammoMgr = ammoMgr;
    return S_OK;
}

void EnemyManager::Update()
{
    for (vecEnemyTankIter = vecEnemyTank.begin(); vecEnemyTankIter != vecEnemyTank.end(); 
        ++vecEnemyTankIter)
    {
        if ((*vecEnemyTankIter)->GetIsAlive())
        {
			(*vecEnemyTankIter)->Update();
        }
        else
        {
            vecEnemyTank.erase(vecEnemyTankIter);
            break;
        }
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
    enemyTank->SetIsAlive(true);
    vecEnemyTank.push_back(enemyTank);
    //m_ammoMgr->AddAmmo(new Ammo, enemyTank);
}

bool EnemyManager::isCollisionPlayer(vector<EnemyTank*>::iterator EnemyTankIter)
{
    auto r1 = (*EnemyTankIter)->GetShape();
    auto r2 = m_player->GetShape();
    if (IntersectRect( &m_tempRect, &r1, &r2) )
    {
		return true;
    }

    return false;
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
