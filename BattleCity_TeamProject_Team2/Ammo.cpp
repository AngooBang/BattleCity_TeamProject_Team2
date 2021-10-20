#include "Ammo.h"
#include "Image.h"
#include "Tank.h"
#include "TileMap.h"
#include "EnemyTank.h"

HRESULT Ammo::Init(POINTFLOAT tankPos, MoveDir moveDir, int ammoSpeed, Image* m_AmmoImage)
{
	m_img = m_AmmoImage;

	m_moveDir = moveDir;
	m_moveSpeed = ammoSpeed;
	m_pos.x = tankPos.x;
	m_pos.y = tankPos.y;
	
	mb_isAlive = true;

	m_shape.left = m_pos.x - m_img->GetWidth() / 2;
	m_shape.right = m_pos.x + m_img->GetWidth() / 2;
	m_shape.top = m_pos.y - m_img->GetHeight() / 2;
	m_shape.bottom = m_pos.y + m_img->GetHeight() / 2;

	return S_OK;
}

void Ammo::Update()
{
	if (!mb_isAlive) return;

	m_pos.x += m_movePosX[m_moveDir] * m_moveSpeed;
	m_pos.y += m_movePosY[m_moveDir] * m_moveSpeed;
	
	SetShape();

	if (CheckInRect(m_shape, m_tileMap->GetShape()))
	{
		mb_isAlive = false;
	}


	switch (m_owner->GetTankType())
	{
	case TankType::Player:
		PlayerAmmoCollider();
		break;
		
	case TankType::Enemy:
		break;

	default:
		break;
	}
}

void Ammo::Render(HDC hdc)
{
	if (!mb_isAlive) return;

	//Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);
	m_img->Render(hdc, m_pos.x, m_pos.y);
}

void Ammo::Relese()
{
	if (m_img)  SAFE_RELEASE(m_img);
}

void Ammo::SetShape()
{
	m_shape.left = m_pos.x - m_img->GetWidth() / 2;
	m_shape.right = m_pos.x + m_img->GetWidth() / 2;
	m_shape.top = m_pos.y - m_img->GetHeight() / 2;
	m_shape.bottom = m_pos.y + m_img->GetHeight() / 2;
}

void Ammo::PlayerAmmoCollider()
{
	EnemyCollider();
	TileCollider();
	
}

void Ammo::EnemyCollider()
{
	vector<EnemyTank*>::iterator it;
	for (it = m_vecEnemys.begin(); it != m_vecEnemys.end();
		++it)
	{
		RECT enemyRC = (*it)->GetShape();
		if (IntersectRect(&m_tempRC, &m_shape, &enemyRC))
		{
			(*it)->SetIsAlive(false);
			mb_isAlive = false;
			break;
		}
	}
}

void Ammo::TileCollider()
{
	for (int i = 0; i < TILE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_COUNT_X; j++)
		{
			for (int k = 0; k < INSIDE_TILE_COUNT_Y; k++)
			{
				for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
				{
					if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain != Terrain::None)
					{
						if (IntersectRect(&m_tempRC, &m_shape, &m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].rc))
						{
							if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain == Terrain::HardWall)
							{
								mb_isAlive = false;
								break;
							}
							switch (m_moveDir)
							{
							case MoveDir::Down:
								if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[0].terrain != Terrain::None)
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[0].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[1].terrain = Terrain::None;
								}
								else
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[2].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[3].terrain = Terrain::None;
								}
								break;
							case MoveDir::Up:
								if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[2].terrain != Terrain::None)
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[2].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[3].terrain = Terrain::None;
								}
								else
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[0].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[1].terrain = Terrain::None;
								}
								break;
							case MoveDir::Right:
								if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[0].terrain != Terrain::None)
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[0].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[2].terrain = Terrain::None;
								}
								else
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[1].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[3].terrain = Terrain::None;
								}
								break;
							case MoveDir::Left:
								if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[1].terrain != Terrain::None)
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[1].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[3].terrain = Terrain::None;
								}
								else
								{
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[0].terrain = Terrain::None;
									m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[2].terrain = Terrain::None;
								}
								break;
							default:
								break;
							}
							mb_isAlive = false;
						}
					}
				}
			}
		}
	}
}
