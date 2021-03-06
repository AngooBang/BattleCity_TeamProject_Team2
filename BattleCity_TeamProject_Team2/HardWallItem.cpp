#include "HardWallItem.h"
#include "TileMap.h"
#include "Image.h"
#include "GameScene.h"

HRESULT HardWallItem::Init()
{
	m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item3.bmp");

	m_pos.x = (float)TILE_MAP_START_POS_X + rand() % (TILE_MAP_SIZE_X);
	m_pos.y = (float)TILE_MAP_START_POS_Y + rand() % (TILE_MAP_SIZE_Y);

	m_bodySize = m_img->GetWidth();
	m_shape.left = (long)m_pos.x - m_bodySize / 2;
	m_shape.top = (long)m_pos.y - m_bodySize / 2;
	m_shape.right = (long)m_pos.x + m_bodySize / 2;
	m_shape.bottom = (long)m_pos.y + m_bodySize / 2;

	mb_isAlive = true;
	mb_isActive = false;
	m_hardWallCount = 0.0f;

	mb_renderScore = false;
	m_elapsedCount2 = 0.0f;

	return S_OK;
}

void HardWallItem::Update()
{
	if (!mb_isAlive && !mb_isActive) return;
	
	if (mb_renderScore == false)
	{
		CountShow();
	}

	if (CheckCollision())
	{
		m_tileMap = m_gameScene->GetTileMap();
		SetHardWall();
		mb_isActive = true;
		//mb_isAlive = false;
		mb_renderScore = true;
		mb_isShow = false;
		m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Point.bmp");
	}
	if (mb_isActive)
	{
		m_hardWallCount += TimerManager::GetSingleton()->GetDeltaTime();
		if (m_hardWallCount > 6.0f)
		{
			ResetHardWall();
			m_hardWallCount = 0.0f;
			mb_isActive = false;
			//mb_isAlive = false;
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

void HardWallItem::Render(HDC hdc)
{
	if (!mb_isAlive) return;

	if (mb_isShow)
		m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y);

	if (mb_renderScore == true)
		m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y, 4, 0, 2.0f);
}

void HardWallItem::Release()
{
	m_gameScene = nullptr;
	m_tileMap = nullptr;
}


void HardWallItem::SetHardWall()
{
	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].terrain == Terrain::Base)
			{
				int key = i * TILE_COUNT_X + j;
				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X]);

				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 1].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 1]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 1]);

				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 2].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 2]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 2]);

				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 3].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 3]);

				m_tileMap->GetTileInfo()[key - 1].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1]);

				m_tileMap->GetTileInfo()[key - 1 + 3].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + 3]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X + 3].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X + 3]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2 + 3].terrain = Terrain::HardWall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2 + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2 + 3]);

				return;
			}
		}
	}
	
}

void HardWallItem::ResetHardWall()
{
	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].terrain == Terrain::Base)
			{
				int key = i * TILE_COUNT_X + j;
				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X]);

				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 1].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 1]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 1]);

				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 2].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 2]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 2]);

				m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 3].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 - TILE_COUNT_X + 3]);

				m_tileMap->GetTileInfo()[key - 1].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1]);

				m_tileMap->GetTileInfo()[key - 1 + 3].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + 3]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X + 3].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X + 3]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2]);

				m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2 + 3].terrain = Terrain::Wall;
				m_tileMap->SetTileFrame(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2 + 3]);
				m_tileMap->SetInTileType(&m_tileMap->GetTileInfo()[key - 1 + TILE_COUNT_X * 2 + 3]);

				return;
			}
		}
	}
}
