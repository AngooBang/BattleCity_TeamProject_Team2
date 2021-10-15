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


	m_tileImage = ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile.bmp", 384, 256, 6, 4, true, RGB(255, 0, 255));

	m_smallTileImage = ImageManager::GetSingleton()->AddImage("Image/BattleCity/SmallSamlpTile.bmp", 96, 64, 6, 4, true, RGB(255, 0, 255));

	m_fp = nullptr;

	m_stageNum = 1;

	m_elapsedCount = 0;
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
						TILE_MAP_START_POS_X + (j * TILE_SIZE + l * (TILE_SIZE / 4)),
						TILE_MAP_START_POS_Y + (i * TILE_SIZE + k * (TILE_SIZE / 4)),
						TILE_MAP_START_POS_X + (j * TILE_SIZE + l * (TILE_SIZE / 4) + (TILE_SIZE / 4)),
						TILE_MAP_START_POS_Y + (i * TILE_SIZE + k * (TILE_SIZE / 4) + (TILE_SIZE / 4)));
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
	m_elapsedCount++;
	if (m_elapsedCount > 40)
	{
		for (int i = 0; i < TILE_COUNT_Y; i++)
		{
			for (int j = 0; j < TILE_COUNT_X; j++)
			{
				if (m_tileInfo[i * TILE_COUNT_X + j].terrain == Terrain::Water)
				{
					m_tileInfo[i * TILE_COUNT_X + j].frameY == 2 ? m_tileInfo[i * TILE_COUNT_X + j].frameY = 3 : m_tileInfo[i * TILE_COUNT_X + j].frameY = 2;
				}
			}
		}
		m_elapsedCount = 0;
	}




	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
		{
			m_tileInfo[1 * TILE_COUNT_X + 1].inTile[testY * INSIDE_TILE_COUNT_X + l].terrain = Terrain::None;
		}
		testY++;
		if (testY > 3)
		{
			testY = 0;
		}
	}
}

void TileMap::Render(HDC hdc)
{
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

	//Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);
}

void TileMap::Release()
{
	SAFE_RELEASE(m_tileImage);
	SAFE_RELEASE(m_smallTileImage);
}

void TileMap::SetTileFrame(TILE_INFO* tileInfo)
{
	switch (tileInfo->terrain)
	{
	case Terrain::None :
		tileInfo->frameX = 5;
		tileInfo->frameY = 0;
		break;
	case Terrain::Wall :
		tileInfo->frameX = 0;
		tileInfo->frameY = 0;
		break;
	case Terrain::HardWall:
		tileInfo->frameX = 0;
		tileInfo->frameY = 1;
		break;
	case Terrain::Water:
		tileInfo->frameX = 0;
		tileInfo->frameY = 2;
		break;
	case Terrain::Grass:
		tileInfo->frameX = 1;
		tileInfo->frameY = 2;
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
				default:
					break;
				}
			}
		}
	}
}
