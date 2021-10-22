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
     //   for (it = vecEnemyTank.begin(); it != vecEnemyTank.end(); ++it)
     //   {
     //       if (vecEnemyTankIter == it) continue;

     //       bool* arr;
     //       RECT tempRC;
     //       RECT r1 = (*it)->GetShape();
     //       POINTFLOAT p1 = (*it)->GetPos();
     //       int b1 = (*it)->GetBodySize();
     //       int s1 = (*it)->GetMoveSpeed();

     //       RECT r2 = (*vecEnemyTankIter)->GetShape();
     //       POINTFLOAT p2 = (*vecEnemyTankIter)->GetPos();
     //       int b2 = (*vecEnemyTankIter)->GetBodySize();
     //       int s2 = (*vecEnemyTankIter)->GetMoveSpeed();
     //       if (IntersectRect(&tempRC, &r1, &r2))
     //       {
     //           MoveDir m1 = (*it)->GetmoveDir();
     //           MoveDir m2 = (*vecEnemyTankIter)->GetmoveDir();

     //           //(*it)->SetMoveSpeed(0);
     //           //(*vecEnemyTankIter)->SetMoveSpeed(0);

     //           switch (m2)
     //           {
     //           case Up:
     //               p2.y = p2.y + (tempRC.bottom - tempRC.top);

     //               (*vecEnemyTankIter)->SetmoveDir(MoveDir::Down);
     //               arr = (*vecEnemyTankIter)->GetDirCehck();
     //               arr[MoveDir::Up] = false;
     //               arr[MoveDir::Down] = true;
     //               (*vecEnemyTankIter)->SetBeforeMoveDir(MoveDir::Down);
     //               (*vecEnemyTankIter)->SetFrameX(4);
     //               (*vecEnemyTankIter)->SetMaxFrameX(5);
     //               break;
     //           case Left:
     //               p2.x = p2.x + (tempRC.right - tempRC.left);

     //               (*vecEnemyTankIter)->SetmoveDir(MoveDir::Right);
     //               arr = (*vecEnemyTankIter)->GetDirCehck();
     //               arr[MoveDir::Left] = false;
     //               arr[MoveDir::Right] = true;
     //               (*vecEnemyTankIter)->SetBeforeMoveDir(MoveDir::Right);
     //               (*vecEnemyTankIter)->SetFrameX(6);
     //               (*vecEnemyTankIter)->SetMaxFrameX(7);
     //               break;
     //           case Down:
     //               p2.y = p2.y - (tempRC.bottom - tempRC.top);

     //               (*vecEnemyTankIter)->SetmoveDir(MoveDir::Up);
     //               arr = (*vecEnemyTankIter)->GetDirCehck();
     //               arr[MoveDir::Down] = false;
     //               arr[MoveDir::Up] = true;
     //               (*vecEnemyTankIter)->SetBeforeMoveDir(MoveDir::Up);
     //               (*vecEnemyTankIter)->SetFrameX(0);
     //               (*vecEnemyTankIter)->SetMaxFrameX(1);
     //               break;
     //           case Right:
     //               p2.x = p2.x - (tempRC.right - tempRC.left);

     //               (*vecEnemyTankIter)->SetmoveDir(MoveDir::Left);
     //               arr = (*vecEnemyTankIter)->GetDirCehck();
     //               arr[MoveDir::Right] = false;
     //               arr[MoveDir::Left] = true;
     //               (*vecEnemyTankIter)->SetBeforeMoveDir(MoveDir::Left);
     //               (*vecEnemyTankIter)->SetFrameX(2);
     //               (*vecEnemyTankIter)->SetMaxFrameX(3);
     //               break;
     //           }

     //           if (m1 != m2)
     //           {
					//switch (m1)
					//{
					//case Up:
					//	p1.y = p1.y + (tempRC.bottom - tempRC.top);

					//	(*it)->SetmoveDir(MoveDir::Down);
					//	arr = (*it)->GetDirCehck();
					//	arr[MoveDir::Up] = false;
					//	arr[MoveDir::Down] = true;
					//	(*it)->SetBeforeMoveDir(MoveDir::Down);
					//	(*it)->SetFrameX(4);
					//	(*it)->SetMaxFrameX(5);
					//	break;
					//case Left:
					//	p1.x = p1.x + (tempRC.right - tempRC.left);

					//	(*it)->SetmoveDir(MoveDir::Right);
					//	arr = (*it)->GetDirCehck();
					//	arr[MoveDir::Left] = false;
					//	arr[MoveDir::Right] = true;
					//	(*it)->SetBeforeMoveDir(MoveDir::Right);
					//	(*it)->SetFrameX(6);
					//	(*it)->SetMaxFrameX(7);
					//	break;
					//case Down:
					//	p1.y = p1.y - (tempRC.bottom - tempRC.top);

					//	(*it)->SetmoveDir(MoveDir::Up);
					//	arr = (*it)->GetDirCehck();
					//	arr[MoveDir::Down] = false;
					//	arr[MoveDir::Up] = true;
					//	(*it)->SetBeforeMoveDir(MoveDir::Up);
					//	(*it)->SetFrameX(0);
					//	(*it)->SetMaxFrameX(1);
					//	break;
					//case Right:
					//	p1.x = p1.x - (tempRC.right - tempRC.left);

					//	(*it)->SetmoveDir(MoveDir::Left);
					//	arr = (*it)->GetDirCehck();
					//	arr[MoveDir::Right] = false;
					//	arr[MoveDir::Left] = true;
					//	(*it)->SetBeforeMoveDir(MoveDir::Left);
					//	(*it)->SetFrameX(2);
					//	(*it)->SetMaxFrameX(3);
					//	break;
					//}
     //           }
     //           
     //           (*it)->SetPos(p1);
     //           (*vecEnemyTankIter)->SetPos(p2);

     //           r1.left = p1.x - (b1 / 2);
     //           r1.top = p1.y - (b1 / 2);
     //           r1.right = r1.left + b1;
     //           r1.bottom = r1.top + b1;

     //           r2.left = p2.x - (b2 / 2);
     //           r2.top = p2.y - (b2 / 2);
     //           r2.right = r2.left + b2;
     //           r2.bottom = r2.top + b2;

     //           (*it)->SetShape(r1);
     //           (*vecEnemyTankIter)->SetShape(r2);

     //           /*(*it)->RandomDirChange();
     //           (*vecEnemyTankIter)->RandomDirChange();*/

     //           /*(*it)->AutoMove();
     //           (*vecEnemyTankIter)->AutoMove();*/

     //       }
     //   }


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
