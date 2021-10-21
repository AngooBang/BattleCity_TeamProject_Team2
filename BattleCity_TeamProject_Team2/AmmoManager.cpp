#include "AmmoManager.h"
#include "Ammo.h"
#include "Tank.h"
#include "EnemyTank.h"
#include "TileMap.h"

HRESULT AmmoManager::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Up.bmp", 9, 12, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Left.bmp", 12, 9, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Down.bmp", 9, 12, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Right.bmp", 12, 9, true, RGB(255, 0, 255));

    m_AmmoImage[MoveDir::Up] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Up.bmp");
    m_AmmoImage[MoveDir::Left] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Left.bmp");
    m_AmmoImage[MoveDir::Down] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Down.bmp");
    m_AmmoImage[MoveDir::Right] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Right.bmp");

    return S_OK;
}

void AmmoManager::Update()
{
    for (m_vecAmmoIter = m_vecAmmo.begin(); m_vecAmmoIter != m_vecAmmo.end();
        ++m_vecAmmoIter)
    {
        AmmoCollision();
        (*m_vecAmmoIter)->SetVecEnemys(m_vecEnemys);
        if((*m_vecAmmoIter)->GetIsAlive() || (*m_vecAmmoIter)->GetTotElapsedCount() < 0.2f)
         (*m_vecAmmoIter)->Update();
        else
        {
            m_vecAmmo.erase(m_vecAmmoIter);
            break;
        }
    }
}

void AmmoManager::Render(HDC hdc)
{
    for (m_vecAmmoIter = m_vecAmmo.begin(); m_vecAmmoIter != m_vecAmmo.end();
        ++m_vecAmmoIter)
    {
        (*m_vecAmmoIter)->Render(hdc);
    }
}

void AmmoManager::Release()
{
    for (m_vecAmmoIter = m_vecAmmo.begin(); m_vecAmmoIter != m_vecAmmo.end();
        ++m_vecAmmoIter)
    {
        SAFE_RELEASE((*m_vecAmmoIter));
    }
}

void AmmoManager::AddAmmo(Ammo* Ammo, Tank* tank)
{
    Ammo->Init(tank->GetPos(), tank->GetmoveDir(),tank->GetammoSpeed(), m_AmmoImage[tank->GetmoveDir()]);
    Ammo->SetOwner(tank);
    Ammo->SetTileMap(m_tileMap);

    //Ammo->Init(tank->GetBarrelend(),  tank->GetmoveDir(), tank->GetammoSpeed(), m_AmmoImage);
    m_vecAmmo.push_back(Ammo);
}

void AmmoManager::AddAmmo(Ammo* Ammo, vector<EnemyTank*>::iterator it, Tank* target)
{
    Ammo->Init((*it)->GetPos(), (*it)->GetmoveDir(), (*it)->GetammoSpeed(), m_AmmoImage[(*it)->GetmoveDir()]);
    Ammo->SetOwner((*it));
    Ammo->SetTileMap(m_tileMap);
    Ammo->SetPlayerTank(target);

    //Ammo->Init(tank->GetBarrelend(),  tank->GetmoveDir(), tank->GetammoSpeed(), m_AmmoImage);
    m_vecAmmo.push_back(Ammo);
}

void AmmoManager::AmmoCollision()
{
    vector<Ammo*>::iterator it;
    for (it = m_vecAmmo.begin(); it != m_vecAmmo.end(); it++)
    {
        if (m_vecAmmoIter == it) continue;
        RECT tempRC;
        RECT r1 = (*m_vecAmmoIter)->GetShape();
        RECT r2 = (*it)->GetShape();
        if (IntersectRect(&tempRC, &r1, &r2))
        {
            (*m_vecAmmoIter)->SetIsAlive(false);
            (*it)->SetIsAlive(false);
            break;
        }
    }
}
