#include "ItemManager.h"
#include "Item.h"
#include "ShieldItem.h"
#include "TimeItem.h"
#include "HardWallItem.h"
#include "StarItem.h"
#include "GranadeItem.h"
#include "LifeItem.h"
#include "GameScene.h"

HRESULT ItemManager::Init()
{
    int i = rand() % 6;
    switch (i)
    {
    case 0:
        m_item = new ShieldItem;
        break;
    case 1:
        m_item = new TimeItem;
        break;
    case 2:
        m_item = new HardWallItem;
        break;
    case 3:
        m_item = new StarItem;
        break;
    case 4:
        m_item = new GranadeItem;
        break;
    case 5:
        m_item = new LifeItem;
        break;
    default:
        break;
    }

    return S_OK;
}

void ItemManager::Update()
{
    for (int i = 0; i < m_vecItems.size(); i++)
    {
         m_vecItems[i]->Update();
    }   

}

void ItemManager::Render(HDC hdc)
{
    for (int i = 0; i < m_vecItems.size(); i++)
    {
        m_vecItems[i]->Render(hdc);
    }
}

void ItemManager::Release()
{
    for (int i = 0; i < m_vecItems.size(); i++)
    {
        SAFE_RELEASE(m_vecItems[i]);
    }
}

void ItemManager::AddItem()
{
    Init();
    m_item->Init();
    m_item->SetGameScene(m_gameScene);
    m_vecItems.push_back(m_item);
}
