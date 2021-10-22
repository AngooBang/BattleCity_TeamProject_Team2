#include "TimeItem.h"
#include "TileMap.h"
#include "Image.h"
#include "GameScene.h"

HRESULT TimeItem::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item2.bmp", 64, 64, true, RGB(255, 0, 255));
	m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item2.bmp");

	m_pos.x = TILE_MAP_START_POS_X + rand() % (TILE_MAP_SIZE_X);
	m_pos.y = TILE_MAP_START_POS_Y + rand() % (TILE_MAP_SIZE_Y);

	m_bodySize = m_img->GetWidth();
	m_shape.left = m_pos.x - m_bodySize / 2;
	m_shape.top = m_pos.y - m_bodySize / 2;
	m_shape.right = m_pos.x + m_bodySize / 2;
	m_shape.bottom = m_pos.y + m_bodySize / 2;

	mb_isAlive = true;
	m_timeStopCount = 0.0f;

	return S_OK;
}

void TimeItem::Update()
{
	if (!mb_isAlive) return;
	CountShow();

	if (m_gameScene->GetIsTimeStop())
	{
		m_timeStopCount += TimerManager::GetSingleton()->GetDeltaTime();

		if (m_timeStopCount > 0.5f)
		{
			m_gameScene->SetIsTimeStop(false);
			m_timeStopCount = 0.0f;
			mb_isAlive = false;
		}
	}

	if (CheckCollision())
	{
		m_gameScene->SetIsTimeStop(true);
	}
}

void TimeItem::Render(HDC hdc)
{
	if (!mb_isAlive) return;

	if (mb_isShow)
		m_img->Render(hdc, m_pos.x, m_pos.y);
}

void TimeItem::Release()
{
}
