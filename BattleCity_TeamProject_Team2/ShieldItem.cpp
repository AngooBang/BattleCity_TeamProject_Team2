#include "ShieldItem.h"
#include "TileMap.h"
#include "Image.h"
#include "GameScene.h"
#include "Tank.h"

HRESULT ShieldItem::Init()
{
	m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item1.bmp");

	m_pos.x = TILE_MAP_START_POS_X + rand() % (TILE_MAP_SIZE_X);
	m_pos.y = TILE_MAP_START_POS_Y + rand() % (TILE_MAP_SIZE_Y);

	m_bodySize = m_img->GetWidth();
	m_shape.left = m_pos.x - m_bodySize / 2;
	m_shape.top = m_pos.y - m_bodySize / 2;
	m_shape.right = m_pos.x + m_bodySize / 2;
	m_shape.bottom = m_pos.y + m_bodySize / 2;

	mb_isAlive = true;
	mb_renderScore = false;
	m_elapsedCount2 = 0.0f;

	return S_OK;
}

void ShieldItem::Update()
{
	if (!mb_isAlive) return;

	if (mb_renderScore == false)
	{
		CountShow();
	}

	if (CheckCollision())
	{
		//mb_isAlive = false;
		m_gameScene->GetPlayer()->ShieldPlayer();
		mb_renderScore = true;
		mb_isShow = false;
		m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Point.bmp");
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

void ShieldItem::Render(HDC hdc)
{
	if (!mb_isAlive) return;

	if (mb_isShow)
		m_img->Render(hdc, m_pos.x, m_pos.y);

	if (mb_renderScore == true)
		m_img->Render(hdc, m_pos.x, m_pos.y, 4, 0, 2.0f);
}
