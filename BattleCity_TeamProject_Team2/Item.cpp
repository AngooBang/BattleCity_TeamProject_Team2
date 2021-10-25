#include "Item.h"
#include "TileMap.h"
#include "Image.h"
#include "GameScene.h"
#include "Tank.h"

HRESULT Item::Init()
{
	return S_OK;
}

void Item::Update()
{
}

void Item::Render(HDC hdc)
{
}

void Item::Release()
{
	m_gameScene = nullptr;
}

void Item::CountShow()
{
	m_elapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
	m_showTimeCount += TimerManager::GetSingleton()->GetDeltaTime();
	if (m_elapsedCount > 0.5f)
	{
		mb_isShow ? mb_isShow = false : mb_isShow = true;

		m_elapsedCount = 0.0f;
	}
	if (m_showTimeCount > 10.0f)
	{
		mb_isAlive = false;
	}
}

bool Item::CheckCollision()
{
	RECT tempRC;
	RECT r1 = m_gameScene->GetPlayer()->GetShape();
	if (IntersectRect(&tempRC, &r1, &m_shape))
	{
		return true;
	}
	else
		return false;
}
