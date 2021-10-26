#include "LifeItem.h"
#include "TileMap.h"
#include "Image.h"
#include "GameScene.h"
#include "Tank.h"

HRESULT LifeItem::Init()
{
	m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item6.bmp");

	m_pos.x = TILE_MAP_START_POS_X + rand() % (TILE_MAP_SIZE_X);
	m_pos.y = TILE_MAP_START_POS_Y + rand() % (TILE_MAP_SIZE_Y);

	m_bodySize = m_img->GetWidth();
	m_shape.left = m_pos.x - m_bodySize / 2;
	m_shape.top = m_pos.y - m_bodySize / 2;
	m_shape.right = m_pos.x + m_bodySize / 2;
	m_shape.bottom = m_pos.y + m_bodySize / 2;

	mb_isAlive = true;

	return S_OK;
}

void LifeItem::Update()
{
	if (!mb_isAlive) return;
	CountShow();

	if (CheckCollision())
	{
		mb_isAlive = false;
		m_gameScene->GetPlayer()->SetHP(1);
	}
}

void LifeItem::Render(HDC hdc)
{
	if (!mb_isAlive) return;

	if (mb_isShow)
		m_img->Render(hdc, m_pos.x, m_pos.y);
}

void LifeItem::Release()
{
}
