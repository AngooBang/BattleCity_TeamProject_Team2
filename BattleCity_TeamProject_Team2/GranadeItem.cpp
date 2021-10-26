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
	mb_renderScore = false;
	m_elapsedCount2 = 0.0f;

	return S_OK;
}

void GranadeItem::Update()
{
	if (!mb_isAlive) return;
	
	if (mb_renderScore == false)
	{
		CountShow();
	}

	if (CheckCollision())
	{
		GameManager::GetSingleton()->TotKillTankNrCalculation(m_gameScene->GetEnemyMgr()->GetVecEnemys().size());
		//cout << m_gameScene->GetEnemyMgr()->GetVecEnemys().size() << endl;
		//cout << GameManager::GetSingleton()->GetKillCount()->totKillTankNr << endl;
		//mb_isAlive = false;
		for (int i = 0; i < m_gameScene->GetEnemyMgr()->GetVecEnemys().size(); i++)
		{
			m_gameScene->GetEnemyMgr()->GetVecEnemys()[i]->SetEnemyStatus(EnemyStatus::Dead);
			m_gameScene->GetEnemyMgr()->GetVecEnemys()[i]->SetHitByGranade(true);
		}
		//m_gameScene->GetEnemyMgr()->GetVecEnemys().clear(); // 왜 동작을 안하지?
		
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

void GranadeItem::Render(HDC hdc)
{
	if (!mb_isAlive) return;
	if (mb_isShow)
		m_img->Render(hdc, m_pos.x, m_pos.y);

	if (mb_renderScore == true)
		m_img->Render(hdc, m_pos.x, m_pos.y, 4, 0, 2.0f);
}

void GranadeItem::Release()
{
}
