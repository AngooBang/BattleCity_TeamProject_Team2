#include "TimeItem.h"
#include "TileMap.h"
#include "Image.h"
#include "GameScene.h"

HRESULT TimeItem::Init()
{
	m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item2.bmp");

	m_pos.x = (float)TILE_MAP_START_POS_X + rand() % (TILE_MAP_SIZE_X);
	m_pos.y = (float)TILE_MAP_START_POS_Y + rand() % (TILE_MAP_SIZE_Y);

	m_bodySize = m_img->GetWidth();
	m_shape.left = (long)m_pos.x - m_bodySize / 2;
	m_shape.top = (long)m_pos.y - m_bodySize / 2;
	m_shape.right = (long)m_pos.x + m_bodySize / 2;
	m_shape.bottom = (long)m_pos.y + m_bodySize / 2;

	mb_isAlive = true;
	mb_isActive = false;
	m_timeStopCount = 0.0f;
	mb_renderScore = false;
	m_elapsedCount2 = 0.0f;

	return S_OK;
}

void TimeItem::Update()
{
	if (!mb_isAlive && !mb_isActive) return;
	
	if (mb_renderScore == false)
	{
		CountShow();
	}

	if (CheckCollision())
	{
		m_gameScene->SetIsTimeStop(true);
		mb_isActive = true;
		//mb_isAlive = false;
		mb_renderScore = true;
		mb_isShow = false;
		m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Point.bmp");
	}
	if (mb_isActive)
	{
		m_timeStopCount += TimerManager::GetSingleton()->GetDeltaTime();

		if (m_timeStopCount > 6.0f)
		{
			m_gameScene->SetIsTimeStop(false);
			m_timeStopCount = 0.0f;
			mb_isActive = false;
		}
	}
	if (mb_renderScore == true)
	{
		m_elapsedCount2 += TimerManager::GetSingleton()->GetDeltaTime();
		if (m_elapsedCount2 > 0.5f)
		{
			mb_renderScore = false;
			m_elapsedCount2 = 0.0f;
			mb_isAlive = false;
		}
	}

}

void TimeItem::Render(HDC hdc)
{
	if (!mb_isAlive) return;

	if (mb_isShow)
		m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y);

	if (mb_renderScore == true)
		m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y, 4, 0, 2.0f);
}

