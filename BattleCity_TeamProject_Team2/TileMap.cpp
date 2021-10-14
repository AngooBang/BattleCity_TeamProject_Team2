#include "TileMap.h"
#include "Image.h"
#include <string>
#include <iostream>

HRESULT TileMap::Init()
{
	m_bodySize = TILE_MAP_SIZE;

	m_shape.left = TILE_MAP_START_POS_X;
	m_shape.top = m_shape.left = TILE_MAP_START_POS_Y;	;
	m_shape.right = m_shape.left + m_bodySize;
	m_shape.bottom = m_shape.top + m_bodySize;


	m_tileImage = ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile.bmp", 96, 64, 6, 4, true, RGB(255, 0, 255));

	m_fp = nullptr;

	m_stageNum = 1;

	m_elapsedCount = 0;
	testY = 0;

	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			SetRect(&(m_tileInfo[i][j].rc),
				TILE_MAP_START_POS_X + (j * TILE_SIZE),
				TILE_MAP_START_POS_Y + (i * TILE_SIZE),
				TILE_MAP_START_POS_X + (j * TILE_SIZE + TILE_SIZE),
				TILE_MAP_START_POS_Y + (i * TILE_SIZE + TILE_SIZE));

			m_tileInfo[i][j].terrain = Terrain::None;

			for (int k = 0; k < INSIDE_TILE_COUNT_Y; k++)
			{
				for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
				{
					SetRect(&(m_tileInfo[i][j].inTile[k][l].rc),
						TILE_MAP_START_POS_X + (j * TILE_SIZE + l * (TILE_SIZE / 4)),
						TILE_MAP_START_POS_Y + (i * TILE_SIZE + k * (TILE_SIZE / 4)),
						TILE_MAP_START_POS_X + (j * TILE_SIZE + l * (TILE_SIZE / 4) + (TILE_SIZE / 4)),
						TILE_MAP_START_POS_Y + (i * TILE_SIZE + k * (TILE_SIZE / 4) + (TILE_SIZE / 4)));
					SetInTileType(&(m_tileInfo[i][j]));
				}
			}

			SetTileFrame(&m_tileInfo[i][j]);
		}
	}


	LoadMapData();

	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			SetTileFrame(&m_tileInfo[i][j]);
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
				if (m_tileInfo[i][j].terrain == Terrain::Water)
				{
					m_tileInfo[i][j].frameY == 2 ? m_tileInfo[i][j].frameY = 3 : m_tileInfo[i][j].frameY = 2;
				}
			}
		}
		m_elapsedCount = 0;
	}




	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
		{
			m_tileInfo[1][1].inTile[testY][l].terrain = Terrain::None;
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
			m_tileImage->Render(hdc, m_tileInfo[i][j].rc.left, m_tileInfo[i][j].rc.top, m_tileInfo[i][j].frameX, m_tileInfo[i][j].frameY, 4.0f);
			for (int k = 0; k < INSIDE_TILE_COUNT_Y; k++)
			{
				for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
				{
					if(m_tileInfo[i][j].inTile[k][l].terrain == Terrain::None)
						m_tileImage->Render(hdc, m_tileInfo[i][j].inTile[k][l].rc.left, m_tileInfo[i][j].inTile[k][l].rc.top, 5, 0);
				}
			}
		}
	}
}

void TileMap::Release()
{
	SAFE_RELEASE(m_tileImage);
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
			tileInfo->inTile[k][l].terrain = tileInfo->terrain;
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
					m_tileInfo[i][j].terrain = Terrain::None;
					SetInTileType(&(m_tileInfo[i][j]));
					break;
				case 1:
					m_tileInfo[i][j].terrain = Terrain::Wall;
					SetInTileType(&(m_tileInfo[i][j]));
					break;
				case 2:
					m_tileInfo[i][j].terrain = Terrain::HardWall;
					SetInTileType(&(m_tileInfo[i][j]));
					break;
				case 3:
					m_tileInfo[i][j].terrain = Terrain::Water;
					SetInTileType(&(m_tileInfo[i][j]));
					break;
				case 4:
					m_tileInfo[i][j].terrain = Terrain::Grass;
					SetInTileType(&(m_tileInfo[i][j]));
					break;
				default:
					break;
				}
			}
		}
	}
}
