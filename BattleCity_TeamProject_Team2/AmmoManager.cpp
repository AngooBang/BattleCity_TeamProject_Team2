#include "AmmoManager.h"
#include "Ammo.h"
#include "Tank.h"

HRESULT AmmoManager::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Up.bmp", 3, 4, 1, 1, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Left.bmp", 4, 3, 1, 1, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Down.bmp", 3, 4, 1, 1, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Right.bmp", 4, 3, 1, 1, true, RGB(255, 0, 255));

    m_AmmoImage[0] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Up.bmp");
    m_AmmoImage[1] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Left.bmp");
    m_AmmoImage[2] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Down.bmp");
    m_AmmoImage[3] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile_Right.bmp");

    return S_OK;
}

void AmmoManager::Update()
{
    for (m_vecAmmoIter = m_vecAmmo.begin(); m_vecAmmoIter != m_vecAmmo.end();
        ++m_vecAmmoIter)
    {
        (*m_vecAmmoIter)->Update();
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
    Ammo->Init(tank->GetBarrelend(), tank->GetmoveDir(),tank->GetammoSpeed(), m_AmmoImage);
    m_vecAmmo.push_back(Ammo);
}