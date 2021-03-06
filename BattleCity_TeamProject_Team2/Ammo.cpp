#include "Ammo.h"
#include "Image.h"
#include "Tank.h"
#include "TileMap.h"
#include "EnemyTank.h"
#include "GameScene.h"
#include "EnemyManager.h"

HRESULT Ammo::Init(POINTFLOAT tankPos, MoveDir moveDir, float ammoSpeed, Image* m_AmmoImage)
{
	m_boomImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Boom_Effect.bmp");

	m_img = m_AmmoImage;


	m_moveDir = moveDir;
	m_moveSpeed = ammoSpeed;
	m_pos.x = tankPos.x;
	m_pos.y = tankPos.y;
	
	mb_isAlive = true;

	m_shape.left = (long)m_pos.x - m_img->GetWidth() / 2;
	m_shape.right = (long)m_pos.x + m_img->GetWidth() / 2;
	m_shape.top = (long)m_pos.y - m_img->GetHeight() / 2;
	m_shape.bottom = (long)m_pos.y + m_img->GetHeight() / 2;

	m_frameX = 0; 
	m_frameY = 0; 
	m_maxFrameX = 2;
	m_elapsedCount = 0;
	m_totElapsedCount = 0;

	m_killCount = GameManager::GetSingleton()->GetKillCount();

	return S_OK;
}

void Ammo::Update()
{
	// 미사일 충돌시 이미지 프레임
	if (!mb_isAlive)
	{
		m_shape.left = m_shape.right = m_shape.top = m_shape.bottom = 0;
		if (m_totElapsedCount < 0.2f)
		{
			m_totElapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
			m_elapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
			if (m_elapsedCount > 0.05f)
			{
				m_frameX++;
				m_elapsedCount = 0;
				if (m_frameX > m_maxFrameX) { m_frameX = 0; }
			}
		}
		return;
	}

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
		EnemyAmmoCollider();
		break;

	default:
		break;
	}
}

void Ammo::Render(HDC hdc)
{
	// 미사일 충돌시 이미지 렌더
	if (!mb_isAlive)
	{
		if (m_totElapsedCount < 0.2f)
		{
			m_boomImg->Render(hdc, (int)m_pos.x, (int)m_pos.y, m_frameX, m_frameY, 3.0f);
		}
	}
	else
	{
		//Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);
		m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y);
	}
	
}

void Ammo::Release()
{
	m_killCount = nullptr;

	m_boomImg = nullptr;
	m_img = nullptr;

	m_owner = nullptr;

	m_enemyMgr = nullptr;

	m_tileMap = nullptr;

	mb_isGameOver = nullptr;
}

void Ammo::SetShape()
{
	m_shape.left = (long)m_pos.x - m_img->GetWidth() / 2;
	m_shape.right = (long)m_pos.x + m_img->GetWidth() / 2;
	m_shape.top = (long)m_pos.y - m_img->GetHeight() / 2;
	m_shape.bottom = (long)m_pos.y + m_img->GetHeight() / 2;
}

void Ammo::PlayerAmmoCollider()
{
	EnemyCollider();
	TileCollider();
}

void Ammo::EnemyCollider()
{
	vector<EnemyTank*>& m_vecEnemys = m_enemyMgr->GetVecEnemys();
	for (int i=0; i< m_vecEnemys.size();i++)
	{
		
		RECT enemyRC = m_vecEnemys[i]->GetShape();
		if (IntersectRect(&m_tempRC, &m_shape, &enemyRC))
		{
			m_vecEnemys[i]->SetHP(-1); // 피격시 Hp 감소
			// 적 Armor탱크 Hp감소에 따른 색깔 변화(이미지 프레임 변화)
			if (m_vecEnemys[i]->GetEnemyType() == EnemyType::ArmorGreen)
			{ 
				m_vecEnemys[i]->SetEnemyType(EnemyType::ArmorYellow);
				m_vecEnemys[i]->SetFrameY((int)EnemyType::ArmorYellow);
			}
			else if (m_vecEnemys[i]->GetEnemyType() == EnemyType::ArmorYellow)
			{ 
				m_vecEnemys[i]->SetEnemyType(EnemyType::ArmorGray);
				m_vecEnemys[i]->SetFrameY((int)EnemyType::ArmorGray);
			}

			// Hp가 0일시
			if (m_vecEnemys[i]->GetHP() == 0)
			{
				m_vecEnemys[i]->SetEnemyStatus(EnemyStatus::Dead);
				
				switch (m_vecEnemys[i]->GetEnemyType())
				{
				case EnemyType::Basic:
					m_killCount->basicTankNr++;
					m_killCount->KillByAmmoTankNr++;
					m_killCount->totKillTankNr++;
					GameManager::GetSingleton()->SetTotScore(100);
					break;

				case EnemyType::Speed:
					m_killCount->speedTankNr++;
					m_killCount->KillByAmmoTankNr++;
					m_killCount->totKillTankNr++;
					GameManager::GetSingleton()->SetTotScore(200);
					break;

				case EnemyType::Power:
					m_killCount->powerTankNr++;
					m_killCount->KillByAmmoTankNr++;
					m_killCount->totKillTankNr++;
					GameManager::GetSingleton()->SetTotScore(300);
					break;

				case EnemyType::ArmorGray:
					m_killCount->armorTankNr++;
					m_killCount->KillByAmmoTankNr++;
					m_killCount->totKillTankNr++;
					GameManager::GetSingleton()->SetTotScore(400);
					break;
				}
			}
			mb_isAlive = false;
			break;
		}
	}
}

void Ammo::EnemyAmmoCollider()
{
	// 적 미사일과 플레이어 탱크 충돌시
	RECT playerTankRect = m_playerTank->GetShape();
	RECT tempRc;
	if (IntersectRect(&tempRc, &m_shape, &playerTankRect))
	{
		m_playerTank->SetHP(-1);
		//if (m_playerTank->GetHP() == 0)
		//{
		//	m_playerTank->SetAlive(false);
		//}
		mb_isAlive = false;
	}

	// 적 미사일과 타일 충돌
	TileCollider();
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
					if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain != Terrain::None &&
						m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain != Terrain::Grass &&
						m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain != Terrain::Water)
					{
						if (IntersectRect(&m_tempRC, &m_shape, &m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].rc))
						{
							if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain == Terrain::HardWall ||
								m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain == Terrain::DestroyBase)
							{
								mb_isAlive = false;
								break;
							}
							if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain == Terrain::Base)
							{
								mb_isAlive = false;
								m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].terrain = Terrain::DestroyBase;
								m_tileMap->SetInTileType(&(m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j]));
								m_tileMap->SetTileFrame(&(m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j]));
								(*mb_isGameOver) = true;
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
