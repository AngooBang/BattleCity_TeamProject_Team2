#include "TileMap.h"
#include "Image.h"
#include <string>
#include <iostream>

HRESULT TileMap::Init()
{
	m_bodySize = TILE_MAP_SIZE_X;

	m_shape.left = TILE_MAP_START_POS_X;
	m_shape.top =  TILE_MAP_START_POS_Y;
	m_shape.right = m_shape.left + TILE_MAP_SIZE_X;
	m_shape.bottom = m_shape.top + TILE_MAP_SIZE_Y;

	mb_destroyBase = false;
	m_frameX = 0;
	m_maxFrameX = 4;

	m_backGround = ImageManager::GetSingleton()->FindImage("Image/TileBackGround.bmp");

	m_tileImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/SamlpTile1.bmp");

	m_smallTileImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/SmallSamlpTile.bmp");

	m_boomImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Boom_Effect2_Tank.bmp");

	m_fp = nullptr;

	m_stageNum = GameManager::GetSingleton()->GetStageNr();

	m_elapsedCount = 0.0f;
	testY = 0;

	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			SetRect(&(m_tileInfo[i * TILE_COUNT_X + j].rc),
				TILE_MAP_START_POS_X + (j * TILE_SIZE),
				TILE_MAP_START_POS_Y + (i * TILE_SIZE),
				TILE_MAP_START_POS_X + (j * TILE_SIZE + TILE_SIZE),
				TILE_MAP_START_POS_Y + (i * TILE_SIZE + TILE_SIZE));

			m_tileInfo[i * TILE_COUNT_X + j].terrain = Terrain::None;

			for (int k = 0; k < INSIDE_TILE_COUNT_Y; k++)
			{
				for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
				{
					SetRect(&(m_tileInfo[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].rc),
						TILE_MAP_START_POS_X + (j * TILE_SIZE + l * (TILE_SIZE / 2)),
						TILE_MAP_START_POS_Y + (i * TILE_SIZE + k * (TILE_SIZE / 2)),
						TILE_MAP_START_POS_X + (j * TILE_SIZE + l * (TILE_SIZE / 2) + (TILE_SIZE / 2)),
						TILE_MAP_START_POS_Y + (i * TILE_SIZE + k * (TILE_SIZE / 2) + (TILE_SIZE / 2)));
					SetInTileType(&(m_tileInfo[i * TILE_COUNT_X + j]));
				}
			}

			SetTileFrame(&m_tileInfo[i * TILE_COUNT_X + j]);
		}
	}


	LoadMapData();

	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			SetTileFrame(&m_tileInfo[i * TILE_COUNT_X + j]);
		}
	}

	return S_OK;
}

void TileMap::Update()
{
	m_elapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
	if (m_elapsedCount > 0.2f)
	{
		for (int i = 0; i < TILE_COUNT_Y; i++)
		{
			for (int j = 0; j < TILE_COUNT_X; j++)
			{
				if (m_tileInfo[i * TILE_COUNT_X + j].terrain == Terrain::Water)
				{
					m_tileInfo[i * TILE_COUNT_X + j].frameX == 0 ? m_tileInfo[i * TILE_COUNT_X + j].frameX = 2 : m_tileInfo[i * TILE_COUNT_X + j].frameX = 0;
				}

				if (m_tileInfo[i * TILE_COUNT_X + j].terrain == Terrain::DestroyBase)
				{
					mb_destroyBase = true;
				}
			}
		}
		if (m_frameX < 0)
		{
			mb_destroyBase = false;
		}
		if (mb_destroyBase)
		{
			if (m_frameX >= m_maxFrameX)
			{
				m_maxFrameX = 0;
				m_frameX--;
			}
			else
			{
				m_maxFrameX = 4;
				m_frameX++;
			}
			m_elapsedCount = 0.0f;
		}
	}

	SetBaseData();

}

void TileMap::Render(HDC hdc)
{
	m_backGround->Render(hdc, TILE_MAP_START_POS_X+TILE_MAP_SIZE_X/2, TILE_MAP_START_POS_Y+TILE_MAP_SIZE_Y/2);

	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			m_tileImage->Render(hdc,
				m_tileInfo[i * TILE_COUNT_X + j].rc.left + TILE_SIZE / 2,
				m_tileInfo[i * TILE_COUNT_X + j].rc.top + TILE_SIZE / 2,
				m_tileInfo[i * TILE_COUNT_X + j].frameX,
				m_tileInfo[i * TILE_COUNT_X + j].frameY);
			//Rectangle(hdc, m_tileInfo[i * TILE_COUNT_Y + j].rc.left, m_tileInfo[i * TILE_COUNT_Y + j].rc.top, m_tileInfo[i * TILE_COUNT_Y + j].rc.right, m_tileInfo[i * TILE_COUNT_Y + j].rc.bottom);
			for (int k = 0; k < INSIDE_TILE_COUNT_Y; k++)
			{
				for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
				{
					if(m_tileInfo[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain == Terrain::None)
						m_smallTileImage->Render(hdc,
							m_tileInfo[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].rc.left + SMALL_TILE_SIZE / 2,
							m_tileInfo[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].rc.top + SMALL_TILE_SIZE / 2,
							5,
							0);
				}
			}
		}
	}
	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			if (m_tileInfo[i * TILE_COUNT_X + j].terrain == Terrain::DestroyBase)
			{
				if (mb_destroyBase)
				{
					if (m_frameX >= 3)
						m_boomImg->Render(hdc, m_tileInfo[i * TILE_COUNT_X + j].rc.right, m_tileInfo[i * TILE_COUNT_X + j].rc.bottom, m_frameX, 0, 2.5f);
					else
						m_boomImg->Render(hdc, m_tileInfo[i * TILE_COUNT_X + j].rc.right, m_tileInfo[i * TILE_COUNT_X + j].rc.bottom, m_frameX, 0, 1.5f);
				}
				return;
			}
		}
	}
	//Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);
}

void TileMap::Release()
{
	m_fp = nullptr;
}

void TileMap::SetTileFrame(TILE_INFO* tileInfo)
{
	switch (tileInfo->terrain)
	{
	case Terrain::None :
		tileInfo->frameX = 10;
		tileInfo->frameY = 10;
		break;
	case Terrain::Wall :
		tileInfo->frameX = 0;
		tileInfo->frameY = 0;
		break;
	case Terrain::HardWall:
		tileInfo->frameX = 0;
		tileInfo->frameY = 2;
		break;
	case Terrain::Water:
		tileInfo->frameX = 0;
		tileInfo->frameY = 6;
		break;
	case Terrain::Grass:
		tileInfo->frameX = 2;
		tileInfo->frameY = 4;
		break;
	case Terrain::Base:
		tileInfo->frameX = 6;
		tileInfo->frameY = 4;
		break;
	case Terrain::DestroyBase:
		tileInfo->frameX = 8;
		tileInfo->frameY = 4;
		break;
	default:
		break;
	}
}

void TileMap::SetInTileType(TILE_INFO* tileInfo)
{
	for (int k = 0; k < INSIDE_TILE_COUNT_Y; k++)
	{
		for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
		{
			tileInfo->inTile[k * INSIDE_TILE_COUNT_Y + l].terrain = tileInfo->terrain;
		}
	}
}

void TileMap::SetBaseData()
{
	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			if (m_tileInfo[i * TILE_COUNT_X + j].terrain == Terrain::DestroyBase)
			{
				if (m_tileInfo[i * TILE_COUNT_X + j - 1].terrain == Terrain::Base)
				{
					// 베이스 시작타일
					m_tileInfo[i * TILE_COUNT_X + j - 1].frameX = 8;
					m_tileInfo[i * TILE_COUNT_X + j - 1].frameY = 4;
					// 베이스 시작타일 기준 우측타일
					m_tileInfo[i * TILE_COUNT_X + j].frameX = 9;
					m_tileInfo[i * TILE_COUNT_X + j].frameY = 4;
					// 베이스 시작타일 기준 아래타일
					m_tileInfo[i * TILE_COUNT_X + j - 1 + TILE_COUNT_X].frameX = 8;
					m_tileInfo[i * TILE_COUNT_X + j - 1 + TILE_COUNT_X].frameY = 5;
					// 베이스 시작타일 기준 아래타일에서 우측타일
					m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].frameX = 9;
					m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].frameY = 5;
					m_tileInfo[i * TILE_COUNT_X + j - 1].terrain =
						m_tileInfo[i * TILE_COUNT_X + j].terrain =
						m_tileInfo[i * TILE_COUNT_X + j - 1 + TILE_COUNT_X].terrain =
						m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].terrain = Terrain::DestroyBase;
					return;
				}
				// 베이스 시작타일
				m_tileInfo[i * TILE_COUNT_X + j].frameX = 8;
				m_tileInfo[i * TILE_COUNT_X + j].frameY = 4;
				// 베이스 시작타일 기준 우측타일
				m_tileInfo[i * TILE_COUNT_X + j + 1].frameX = 9;
				m_tileInfo[i * TILE_COUNT_X + j + 1].frameY = 4;
				// 베이스 시작타일 기준 아래타일
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].frameX = 8;
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].frameY = 5;
				// 베이스 시작타일 기준 아래타일에서 우측타일
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X + 1].frameX = 9;
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X + 1].frameY = 5;
				m_tileInfo[i * TILE_COUNT_X + j].terrain =
					m_tileInfo[i * TILE_COUNT_X + j + 1].terrain =
					m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].terrain =
					m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X + 1].terrain = Terrain::DestroyBase;
				return;
			}
			if (m_tileInfo[i * TILE_COUNT_X + j].terrain == Terrain::Base)
			{
				if (m_tileInfo[i * TILE_COUNT_X + j - 1].terrain == Terrain::Base) continue;
				if (m_tileInfo[i * TILE_COUNT_X + j - TILE_COUNT_X].terrain == Terrain::Base) continue;
				// 베이스 시작타일
				m_tileInfo[i * TILE_COUNT_X + j].frameX = 6;
				m_tileInfo[i * TILE_COUNT_X + j].frameY = 4;
				// 베이스 시작타일 기준 우측타일
				m_tileInfo[i * TILE_COUNT_X + j + 1].frameX = 7;
				m_tileInfo[i * TILE_COUNT_X + j + 1].frameY = 4;
				// 베이스 시작타일 기준 아래타일
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].frameX = 6;
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X].frameY = 5;
				// 베이스 시작타일 기준 아래타일에서 우측타일
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X + 1].frameX = 7;
				m_tileInfo[i * TILE_COUNT_X + j + TILE_COUNT_X + 1].frameY = 5;
			}
		}
	}
}

void TileMap::LoadMapData()
{
	string s = "StageData/Stage" + to_string(m_stageNum) + ".txt";
	const char* fileName = s.c_str();

	fopen_s(&m_fp, fileName, "r");

	if (m_fp != nullptr)
	{
		for (int i = 0; i < TILE_COUNT_Y; i++)
		{
			for (int j = 0; j < TILE_COUNT_X; j++)
			{
				int tileType;
				fscanf_s(m_fp, "%d", &tileType);
				switch (tileType)
				{
				case 0:
					m_tileInfo[i * TILE_COUNT_Y + j].terrain = Terrain::None;
					SetInTileType(&(m_tileInfo[i * TILE_COUNT_Y + j]));
					break;
				case 1:
					m_tileInfo[i * TILE_COUNT_Y + j].terrain = Terrain::Wall;
					SetInTileType(&(m_tileInfo[i * TILE_COUNT_Y + j]));
					break;
				case 2:
					m_tileInfo[i * TILE_COUNT_Y + j].terrain = Terrain::HardWall;
					SetInTileType(&(m_tileInfo[i * TILE_COUNT_Y + j]));
					break;
				case 3:
					m_tileInfo[i * TILE_COUNT_Y + j].terrain = Terrain::Water;
					SetInTileType(&(m_tileInfo[i * TILE_COUNT_Y + j]));
					break;
				case 4:
					m_tileInfo[i * TILE_COUNT_Y + j].terrain = Terrain::Grass;
					SetInTileType(&(m_tileInfo[i * TILE_COUNT_Y + j]));
					break;
				case 5:
					m_tileInfo[i * TILE_COUNT_Y + j].terrain = Terrain::Base;
					SetInTileType(&(m_tileInfo[i * TILE_COUNT_Y + j]));
					break;
				default:
					break;
				}
			}
		}
	}
}
