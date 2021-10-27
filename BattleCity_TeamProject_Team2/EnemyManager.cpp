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
            // Àû ÅÊÅ©³¢¸® Ãæµ¹
               if (vecEnemyTank[j] == vecEnemyTank[i]) continue;
               CollisionEnemyTank(i, j);
           }

        if (vecEnemyTank[i]->GetIsAlive())
        {
            // ÃÑ¾Ë ¹ß»ç
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

void EnemyManager::CollisionEnemyTank(int i , int j)
{
    RECT tempRC;

    RECT firstTankShape = vecEnemyTank[j]->GetShape();
    POINTFLOAT firstTankPos = vecEnemyTank[j]->GetPos();
    int firstTankBodySize = vecEnemyTank[j]->GetBodySize();

    RECT SecondTankShape = vecEnemyTank[i]->GetShape();
    POINTFLOAT SecondTankPos = vecEnemyTank[i]->GetPos();
    int SecondTankBodySize = vecEnemyTank[i]->GetBodySize();

    if (IntersectRect(&tempRC, &firstTankShape, &SecondTankShape))
    {
        if ((tempRC.right - tempRC.left) > (tempRC.bottom - tempRC.top))
        {
            SecondTankPos.y = SecondTankPos.y + (tempRC.bottom - tempRC.top) / 2;
            firstTankPos.y = firstTankPos.y - (tempRC.bottom - tempRC.top) / 2;
        }
        else
        {
            if (firstTankPos.x < SecondTankPos.x)
            {
                SecondTankPos.x = SecondTankPos.x + (tempRC.right - tempRC.left) / 2;
                firstTankPos.x = firstTankPos.x - (tempRC.right - tempRC.left) / 2;
            }
            else
            {
                SecondTankPos.x = SecondTankPos.x - (tempRC.right - tempRC.left) / 2;
                firstTankPos.x = firstTankPos.x + (tempRC.right - tempRC.left) / 2;
            }
        }

        vecEnemyTank[j]->SetPos(firstTankPos);
        vecEnemyTank[i]->SetPos(SecondTankPos);

        firstTankShape.left = (long)firstTankPos.x - (firstTankBodySize / 2);
        firstTankShape.top = (long)firstTankPos.y - (firstTankBodySize / 2);
        firstTankShape.right = (long)firstTankShape.left + firstTankBodySize;
        firstTankShape.bottom = (long)firstTankShape.top + firstTankBodySize;

        SecondTankShape.left = (long)SecondTankPos.x - (SecondTankBodySize / 2);
        SecondTankShape.top = (long)SecondTankPos.y - (SecondTankBodySize / 2);
        SecondTankShape.right = (long)SecondTankShape.left + SecondTankBodySize;
        SecondTankShape.bottom = (long)SecondTankShape.top + SecondTankBodySize;

        vecEnemyTank[j]->SetShape(firstTankShape);
        vecEnemyTank[i]->SetShape(SecondTankShape);

        vecEnemyTank[j]->RandomDirChange();
        vecEnemyTank[i]->RandomDirChange();
    }
}

