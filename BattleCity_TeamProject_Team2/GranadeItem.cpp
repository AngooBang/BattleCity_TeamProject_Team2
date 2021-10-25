#include "GranadeItem.h"
#include "Image.h"
#include "TileMap.h"
#include "GameScene.h"
#include "EnemyManager.h"
#include "EnemyTank.h"

HRESULT GranadeItem::Init()
{
	m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item5.bmp");

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

void GranadeItem::Update()
{
	if (!mb_isAlive) return;
	CountShow();

	if (CheckCollision())
	{
		GameManager::GetSingleton()->TotKillTankNrCalculation(m_gameScene->GetEnemyMgr()->GetVecEnemys().size());
		
		mb_isAlive = false;
		for (int i = 0; i < m_gameScene->GetEnemyMgr()->GetVecEnemys().size(); i++)
		{
			m_gameScene->GetEnemyMgr()->GetVecEnemys()[i]->SetEnemyStatus(EnemyStatus::Dead);
		}
	}
}

void GranadeItem::Render(HDC hdc)
{
	if (!mb_isAlive) return;
	if (mb_isShow)
		m_img->Render(hdc, m_pos.x, m_pos.y);
}

