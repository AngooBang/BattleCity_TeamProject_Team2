#include "EnemyTank.h"
#include "EnemyManager.h"
#include "Image.h"
#include "TileMap.h"

HRESULT EnemyTank::Init(POINTFLOAT pos, EnemyManager* manager)
{
    //ImageManager::GetSingleton()->AddImage("Image/Taeyeon.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    //m_backGround = ImageManager::GetSingleton()->FindImage("Image/Taeyeon.bmp");
    return S_OK;
}

void EnemyTank::Update()
{    
}

void EnemyTank::Render(HDC hdc)
{
}

void EnemyTank::Release()
{
    //if(m_backGround) SAFE_RELEASE(m_backGround);
}

void EnemyTank::AutoMove()
{
    /*if (m_shape.right >= m_mapShape.right)
    {
        m_moveDir = MoveDir::Left;
        m_frameX = m_enemyFrame[MoveDir::Left];
        m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;
    }
    else if (m_shape.left <= m_mapShape.left)
    {
        m_moveDir = MoveDir::Right;
        m_frameX = m_enemyFrame[MoveDir::Right];
        m_maxFrameX = m_enemyFrame[MoveDir::Right] + 1;
    }
    else if (m_shape.top <= m_mapShape.top)
    {
        m_moveDir = MoveDir::Down;
        m_frameX = m_enemyFrame[MoveDir::Down];
        m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
    }
    else if (m_shape.bottom >= m_mapShape.bottom)
    {
        m_moveDir = MoveDir::Up;
        m_frameX = m_enemyFrame[MoveDir::Up];
        m_maxFrameX = m_enemyFrame[MoveDir::Up] + 1;
    }*/

    switch (m_moveDir)
    {
    case MoveDir::Left:		m_pos.x -= m_moveSpeed; break;
    case MoveDir::Right:	m_pos.x += m_moveSpeed; break;
    case MoveDir::Up:	    m_pos.y -= m_moveSpeed; break;
    case MoveDir::Down:	    m_pos.y += m_moveSpeed; break;
    }

    m_shape.left = m_pos.x - (m_bodySize / 2);
    m_shape.top = m_pos.y - (m_bodySize / 2);
    m_shape.right = m_shape.left + m_bodySize;
    m_shape.bottom = m_shape.top + m_bodySize;
}

void EnemyTank::RandomDirChange()
{
	while (true)
	{
		int RandomValue = rand() % 100 + 1;
		if (RandomValue > 0 && RandomValue <= 25)
		{
			m_moveDir = MoveDir::Up;
			m_frameX = m_enemyFrame[MoveDir::Up];
			m_maxFrameX = m_enemyFrame[MoveDir::Up] + 1;
		}
		else if (RandomValue > 25 && RandomValue <= 50)
		{
			m_moveDir = MoveDir::Left;
			m_frameX = m_enemyFrame[MoveDir::Left];
			m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;
		}
		else if (RandomValue > 50 && RandomValue <= 75)
		{
			m_moveDir = MoveDir::Down;
			m_frameX = m_enemyFrame[MoveDir::Down];
			m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
		}
		else
		{
			m_moveDir = MoveDir::Right;
			m_frameX = m_enemyFrame[MoveDir::Right];
			m_maxFrameX = m_enemyFrame[MoveDir::Right] + 1;
		}

		if (mb_dirCheck[m_moveDir] != true) break;
	}

	mb_dirCheck[m_beforeMoveDir] = false;
	mb_dirCheck[m_moveDir] = true;
	m_beforeMoveDir = m_moveDir;
}

bool EnemyTank::IsCollisionMap()
{
    // 탱크가 화면과 충돌시 방향전환
    if (m_shape.right > m_tileMap->GetShape().right || m_shape.left < m_tileMap->GetShape().left
        || m_shape.top < m_tileMap->GetShape().top || m_shape.bottom > m_tileMap->GetShape().bottom)
    {
        return true;
    }

    return false;
}

bool EnemyTank::IsCollisionTile()
{
	// 각 타일 충돌 비교
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

							return true;
						}
					}
				}
			}

		}
	}

    return false;
}

void EnemyTank::MoveCorrection()
{
	if (m_isCollide[MoveDir::Up] && m_moveDir == MoveDir::Up)
	{
		if (m_tempRC.right - m_tempRC.left > MOVE_CORRECTION_VALUE)
		{
			m_pos.y = m_pos.y + (m_tempRC.bottom - m_tempRC.top);
			RandomDirChange();
		}
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
		{
			m_pos.x = m_pos.x + (m_tempRC.right - m_tempRC.left);
			RandomDirChange();
		}
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
		{
			m_pos.y = m_pos.y - (m_tempRC.bottom - m_tempRC.top);
			RandomDirChange();
		}
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
		{
			m_pos.x = m_pos.x - (m_tempRC.right - m_tempRC.left);
			RandomDirChange();
		}
		else
		{
			if ((m_shape.top + m_shape.bottom) / 2 > m_tempRC.bottom)
				m_pos.y++;
			else if ((m_shape.top + m_shape.bottom) / 2 < m_tempRC.top)
				m_pos.y--;
		}
	}
}
