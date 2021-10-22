#include "EnemyManager.h"
#include "EnemyTank.h"
#include "TileMap.h"
#include "Tank.h"
#include "AmmoManager.h"
#include "Ammo.h"

HRESULT EnemyManager::Init()
{
    return S_OK;
}

void EnemyManager::Update()
{
    for (vecEnemyTankIter = vecEnemyTank.begin(); vecEnemyTankIter != vecEnemyTank.end(); 
        ++vecEnemyTankIter)
    {
        vector<EnemyTank*>::iterator it;

        if ((*vecEnemyTankIter)->GetIsAlive())
        {
            if ((*vecEnemyTankIter)->GetisFire() == true)
            {
                m_ammoMgr->AddAmmo(new Ammo, vecEnemyTankIter, m_player);
                (*vecEnemyTankIter)->SetisFire(false);
            }

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
    enemyTank->SetGameScene(m_gameScene);
    vecEnemyTank.push_back(enemyTank);
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

