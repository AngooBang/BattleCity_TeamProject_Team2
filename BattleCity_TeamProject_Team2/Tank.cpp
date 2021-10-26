#include "Tank.h"
#include "Ammo.h"
#include "AmmoManager.h"
#include "Image.h"
#include "TileMap.h"

HRESULT Tank::Init()
{
	m_type = TankType::Player;
	m_HP = GameManager::GetSingleton()->GetPlayerHp();
	m_tempHP = m_HP;

	m_shieldImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Shield.bmp");

	SpawnPlayer();

	m_bodySize = 64;

	m_moveSpeed = 3;
	m_moveDir = MoveDir::Up;

	mb_isAlive = true;
	mb_isShield = false;
	mb_Move = false;

	m_ammoSpeed = 10;


	for (int i = 0; i < MoveDir::End; i++)
	{
		m_isCollide[i] = false;
	}

	m_Barrelend.x = m_pos.x;
	m_Barrelend.y = m_pos.y - 32;

	//m_frameY = 0;
	m_frameY = GameManager::GetSingleton()->GetPlayerFrameY();

	// 나중에...
	return S_OK;
}

void Tank::Update()
{
	// 아이템을 먹어 체력이 높아졌을때
	if (m_tempHP < m_HP)
	{
		m_tempHP = m_HP;
	}
	if (mb_isSpawn)
	{
		m_spawnTimer += TimerManager::GetSingleton()->GetDeltaTime();
		m_HP = m_tempHP;

		if (m_spawnTimer > 1.5f)
		{
			m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");

			m_frameX = m_moveDir * 2;
			m_maxFrameX = m_frameX + 1;
			m_spawnTimer = 0.0f;
			mb_isSpawn = false;
			ShieldPlayer();
		}
	}
	else
	{

		if (mb_isShield)
		{
			m_shieldTimer += TimerManager::GetSingleton()->GetDeltaTime();
			m_HP = m_tempHP;

			if (m_elapsedCount % 5 == 0)
			{
				m_shieldframeX == 0 ? m_shieldframeX = 1 : m_shieldframeX = 0;
			}

			if (m_shieldTimer > 4.0f)
			{
				mb_isShield = false;
				m_shieldTimer = 0.0f;
			}
		}
		if (m_tempHP > m_HP)
		{
			SpawnPlayer();
			m_tempHP = m_HP;
		}
#pragma region 입력부

		if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
		{
			mb_isFire = true;
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			//SetMoveDir(MoveDir::Left);

			if (m_moveDir != MoveDir::Left)
			{
				m_moveDir = MoveDir::Left;
				m_frameX = (int)m_moveDir * 2;
				m_maxFrameX = (int)m_moveDir * 2 + 1;
			}
			mb_Move = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			//SetMoveDir(MoveDir::Right);

			if (m_moveDir != MoveDir::Right)
			{
				m_moveDir = MoveDir::Right;
				m_frameX = (int)m_moveDir * 2;
				m_maxFrameX = (int)m_moveDir * 2 + 1;
			}
			mb_Move = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{
			//SetMoveDir(MoveDir::Up);

			if (m_moveDir != MoveDir::Up)
			{
				m_moveDir = MoveDir::Up;
				m_frameX = (int)m_moveDir * 2;
				m_maxFrameX = (int)m_moveDir * 2 + 1;
			}
			mb_Move = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		{
			//SetMoveDir(MoveDir::Down);

			if (m_moveDir != MoveDir::Down)
			{
				m_moveDir = MoveDir::Down;
				m_frameX = (int)m_moveDir * 2;
				m_maxFrameX = (int)m_moveDir * 2 + 1;
			}
			mb_Move = true;
		}
		else
		{
			mb_Move = false;
		}
#pragma endregion
#pragma region 충돌처리부
		// 타일맵 프레임 충돌비교
		if (CheckInRect(m_shape, m_tileMap->GetShape()))
		{
			if (m_shape.top <= m_tileMap->GetShape().top)
				if (m_moveDir == MoveDir::Up)
					mb_Move = false;
				else
					m_isCollide[MoveDir::Up] = false;
			if (m_shape.left <= m_tileMap->GetShape().left)
				if (m_moveDir == MoveDir::Left)
					mb_Move = false;
				else
					m_isCollide[MoveDir::Left] = false;
			if (m_shape.bottom >= m_tileMap->GetShape().bottom)
				if (m_moveDir == MoveDir::Down)
					mb_Move = false;
				else
					m_isCollide[MoveDir::Down] = false;
			if (m_shape.right >= m_tileMap->GetShape().right)
				if (m_moveDir == MoveDir::Right)
					mb_Move = false;
				else
					m_isCollide[MoveDir::Right] = false;
		}
		else
		{
			for (int i = 0; i < MoveDir::End; i++)
			{
				m_isCollide[i] = false;
			}
		}

		// 각 타일 충돌 비교
		for (int i = 0; i < TILE_COUNT_Y; i++)
		{
			for (int j = 0; j < TILE_COUNT_X; j++)
			{
				for (int k = 0; k < INSIDE_TILE_COUNT_Y; k++)
				{
					for (int l = 0; l < INSIDE_TILE_COUNT_X; l++)
					{
						if (m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain != Terrain::None &&
							m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].terrain != Terrain::Grass)
						{
							if (IntersectRect(&m_tempRC, &m_shape, &m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].inTile[k * INSIDE_TILE_COUNT_X + l].rc))
								//if (CheckCollision(m_shape, m_tileMap->GetTileInfo()[i * TILE_COUNT_X + j].rc))
							{
								if (m_tempRC.bottom < ((m_shape.top + m_shape.bottom) / 2))
								{
									m_isCollide[MoveDir::Up] = true;
								}
								else
								{
									m_isCollide[MoveDir::Up] = false;
								}
								if (m_tempRC.right < ((m_shape.left + m_shape.right) / 2))
								{
									m_isCollide[MoveDir::Left] = true;
								}
								else
								{
									m_isCollide[MoveDir::Left] = false;
								}
								if (m_tempRC.top > ((m_shape.top + m_shape.bottom) / 2))
								{
									m_isCollide[MoveDir::Down] = true;
								}
								else
								{
									m_isCollide[MoveDir::Down] = false;
								}
								if (m_tempRC.left > ((m_shape.left + m_shape.right) / 2))
								{
									m_isCollide[MoveDir::Right] = true;
								}
								else
								{
									m_isCollide[MoveDir::Right] = false;
								}
								MoveCorrection();
							}
						}
					}
				}
			}
		}
#pragma endregion
#pragma region 이동값 처리부

		if (mb_Move)
		{
			switch (m_moveDir)
			{
			case MoveDir::Left:
				m_pos.x -= m_moveSpeed;
				break;
			case MoveDir::Right:
				m_pos.x += m_moveSpeed;
				break;
			case MoveDir::Up:
				m_pos.y -= m_moveSpeed;
				break;
			case MoveDir::Down:
				m_pos.y += m_moveSpeed;
				break;
			}
		}
#pragma endregion
	}
#pragma region 이미지 처리부
	SetImage();
#pragma endregion
	//SetBarrel(m_BarrelPosX[(int)m_moveDir], m_BarrelPosY[(int)m_moveDir]);
	SetShape();
}

void Tank::Render(HDC hdc)
{
	//Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);

	m_img->Render(hdc, m_pos.x, m_pos.y, m_frameX, m_frameY);

	if (mb_isShield)
		m_shieldImg->Render(hdc, m_pos.x, m_pos.y, m_shieldframeX, 0);

}

void Tank::Release()
{
	//if (m_img)  SAFE_RELEASE(m_img);
}

void Tank::SetBarrel(int x, int y)
{
	m_Barrelend.x = m_pos.x + x;
	m_Barrelend.y = m_pos.y + y;
}

void Tank::SetPosMove(int x, int y)
{
	m_pos.x += x * m_moveSpeed;
	m_pos.y += y * m_moveSpeed;
}

void Tank::SetMoveDir(MoveDir moveDir)
{
	if (m_moveDir != moveDir)
	{
		m_moveDir = moveDir;
		m_frameX = (int)m_moveDir * 2;
		m_maxFrameX = (int)m_moveDir * 2 + 1;
	}
	mb_Move = true;
}

void Tank::SetShape()
{
	m_shape.left = m_pos.x - m_bodySize / 2;
	m_shape.right = m_pos.x + m_bodySize / 2 - 4;
	m_shape.top = m_pos.y - m_bodySize / 2;
	m_shape.bottom = m_pos.y + m_bodySize / 2;
}

void Tank::MoveCorrection()
{
	if (m_isCollide[MoveDir::Up] && m_moveDir == MoveDir::Up)
	{
		if (m_tempRC.right - m_tempRC.left > MOVE_CORRECTION_VALUE)
			mb_Move = false;
		else
		{
			if ((m_shape.left + m_shape.right) / 2 > m_tempRC.right)
				m_pos.x++;
			else if ((m_shape.left + m_shape.right) / 2 < m_tempRC.left)
				m_pos.x--;
		}
	}
	if (m_isCollide[MoveDir::Left] && m_moveDir == MoveDir::Left)
	{
		if (m_tempRC.bottom - m_tempRC.top > MOVE_CORRECTION_VALUE)
			mb_Move = false;
		else
		{
			if ((m_shape.top + m_shape.bottom) / 2 > m_tempRC.bottom)
				m_pos.y++;
			else if ((m_shape.top + m_shape.bottom) / 2 < m_tempRC.top)
				m_pos.y--;
		}
	}
	if (m_isCollide[MoveDir::Down] && m_moveDir == MoveDir::Down)
	{
		if (m_tempRC.right - m_tempRC.left > MOVE_CORRECTION_VALUE)
			mb_Move = false;
		else
		{
			if ((m_shape.left + m_shape.right) / 2 > m_tempRC.right)
				m_pos.x++;
			else if ((m_shape.left + m_shape.right) / 2 < m_tempRC.left)
				m_pos.x--;
		}
	}

	if (m_isCollide[MoveDir::Right] && m_moveDir == MoveDir::Right)
	{
		if (m_tempRC.bottom - m_tempRC.top > MOVE_CORRECTION_VALUE)
			mb_Move = false;
		else
		{
			if ((m_shape.top + m_shape.bottom) / 2 > m_tempRC.bottom)
				m_pos.y++;
			else if ((m_shape.top + m_shape.bottom) / 2 < m_tempRC.top)
				m_pos.y--;
		}
	}
}

void Tank::SpawnPlayer()
{
	m_spawnTimer = 0;

	m_pos.x = TILE_MAP_SIZE_X / 2 - 112;
	m_pos.y = TILE_MAP_SIZE_Y - 32;

	m_frameX = 0;
	m_frameY = 0;
	m_maxFrameX = 2;

	mb_isSpawn = true;
	m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Spawn_Effect2.bmp");
}

void Tank::ShieldPlayer()
{
	m_shieldframeX = 0;
	m_shieldTimer = 0.0f;
	mb_isShield = true;
}

void Tank::UpgradeTank()
{
	++m_frameY;

	if (m_frameY > 3)
	{
		m_frameY = 3;
	}
}

void Tank::SetImage()
{
	++m_elapsedCount;
	if (mb_isSpawn)
	{
		if (m_elapsedCount % 5 == 0)
		{
			if (m_frameX >= m_maxFrameX)
			{
				m_maxFrameX = 0;
				m_frameX--;
			}
			else
			{
				m_maxFrameX = 2;
				m_frameX++;	
			}
			m_elapsedCount = 0;
		}
	}
	else if (mb_Move)
	{
		if (m_elapsedCount % 5 == 0)
		{
			++m_frameX;
			if (m_frameX > m_maxFrameX)
			{
				m_frameX -= 2;
			}
			m_elapsedCount = 0;
		}
	}
}

void Tank::CheckCollisionDir(RECT a, RECT b)
{
	if (a.left < b.right)
		m_isCollide[MoveDir::Left] = true;
	if (a.top < b.bottom)
		m_isCollide[MoveDir::Up] = true;
	if (a.right > b.left)
		m_isCollide[MoveDir::Right] = true;
	if (a.bottom > b.top)
		m_isCollide[MoveDir::Down] = true;
}

