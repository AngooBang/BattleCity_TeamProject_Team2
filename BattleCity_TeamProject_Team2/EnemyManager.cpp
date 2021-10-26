#include "EnemyManager.h"
#include "EnemyTank.h"
#include "TileMap.h"
#include "Tank.h"
#include "AmmoManager.h"
#include "Ammo.h"

#include "GameScene.h"

HRESULT EnemyManager::Init()
{
    return S_OK;
}

void EnemyManager::Update()
{
    for (int i = 0; i < vecEnemyTank.size(); ++i)
    {
        for (int j = 0; j < vecEnemyTank.size(); ++j)
           {
               if (vecEnemyTank[j] == vecEnemyTank[i]) continue;

               bool* arr1;
               arr1 = vecEnemyTank[j]->GetDirCehck();
               RECT tempRC;
               RECT r1 = vecEnemyTank[j]->GetShape();
               POINTFLOAT p1 = vecEnemyTank[j]->GetPos();
               int b1 = vecEnemyTank[j]->GetBodySize();
               int s1 = vecEnemyTank[j]->GetMoveSpeed();
               MoveDir m1 = vecEnemyTank[j]->GetmoveDir();

               bool* arr;
               arr = vecEnemyTank[i]->GetDirCehck();
               RECT r2 = vecEnemyTank[i]->GetShape();
               POINTFLOAT p2 = vecEnemyTank[i]->GetPos();
               int b2 = vecEnemyTank[i]->GetBodySize();
               int s2 = vecEnemyTank[i]->GetMoveSpeed();
               MoveDir m2 = vecEnemyTank[i]->GetmoveDir();

               if (IntersectRect(&tempRC, &r1, &r2))
               {
                   if ((tempRC.right - tempRC.left) > (tempRC.bottom - tempRC.top))
                   {
					   p2.y = p2.y + (tempRC.bottom - tempRC.top) / 2;
                       p1.y = p1.y - (tempRC.bottom - tempRC.top) / 2;
                   }
                   else
                   {
                       if (p1.x < p2.x)
                       {
                           p2.x = p2.x + (tempRC.right - tempRC.left) / 2;
                           p1.x = p1.x - (tempRC.right - tempRC.left) / 2;
                       }
                       else
                       {
                           p2.x = p2.x - (tempRC.right - tempRC.left) / 2;
                           p1.x = p1.x + (tempRC.right - tempRC.left) / 2;
                       }
                   }                  

                   vecEnemyTank[j]->SetPos(p1);
                   vecEnemyTank[i]->SetPos(p2);

                   r1.left = p1.x - (b1 / 2);
                   r1.top = p1.y - (b1 / 2);
                   r1.right = r1.left + b1;
                   r1.bottom = r1.top + b1;

                   r2.left = p2.x - (b2 / 2);
                   r2.top = p2.y - (b2 / 2);
                   r2.right = r2.left + b2;
                   r2.bottom = r2.top + b2;

                   vecEnemyTank[j]->SetShape(r1);
                   vecEnemyTank[i]->SetShape(r2);

                   vecEnemyTank[j]->RandomDirChange();
                   vecEnemyTank[i]->RandomDirChange();
               }
           }

        if (vecEnemyTank[i]->GetIsAlive())
        {
            if (vecEnemyTank[i]->GetisFire() == true)
            {
                m_ammoMgr->AddAmmo(new Ammo, vecEnemyTank.begin()+i, m_player);
                vecEnemyTank[i]->SetisFire(false);
            }

            vecEnemyTank[i]->Update();
        }
        else
        {
            delete vecEnemyTank[i];
            vecEnemyTank.erase(vecEnemyTank.begin() + i);
            break;
        }
    }
}

void EnemyManager::Render(HDC hdc)
{

    for (int i = 0; i < vecEnemyTank.size(); ++i)
    {
        vecEnemyTank[i]->Render(hdc);
    }
}

void EnemyManager::Release()
{

    for (int i = 0; i < vecEnemyTank.size(); ++i)
    {
        SAFE_RELEASE(vecEnemyTank[i]);
    }
    vecEnemyTank.clear();

    m_player = nullptr;
    m_gameScene = nullptr;
    m_ammoMgr = nullptr;
    m_tileMap = nullptr;
    //SAFE_RELEASE(m_gameScene);
    //SAFE_RELEASE(m_ammoMgr);
    //SAFE_RELEASE(m_tileMap);
}

void EnemyManager::AddEnemy(EnemyTank* enemyTank, POINTFLOAT pos)
{
    enemyTank->Init(pos);
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

