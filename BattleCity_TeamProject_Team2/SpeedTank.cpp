#include "SpeedTank.h"
#include "Image.h"
#include "TileMap.h"
#include "GameScene.h"

HRESULT SpeedTank::Init(POINTFLOAT pos)
{
    m_moveDir = MoveDir::Down;
    m_elapsedCount = 0;
    m_moveDelay = 70;

    m_frameCount = 1;

    totElapsedCount = 0.0f;
    m_fireElapsedCount = 0.0f;
    m_renderScore = false;
    m_hitByGranade = false;
    mb_isReady = true;


    m_type = TankType::Enemy;
    m_enemyTankType = EnemyType::Speed;
    m_HP = 1;
    m_ammoSpeed = (int)BulletSpeed::Normal;
    //m_Barrelend = { pos.x, pos.y };

    mb_isAlive = true;
    //mb_Move = false;
    mb_isFire = false;


    m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Spawn_Effect2.bmp");

    m_pos.x = pos.x;
    m_pos.y = pos.y;

    m_bodySize = 0;

    m_shape.left = (long)m_pos.x - (m_bodySize / 2);
    m_shape.top = (long)m_pos.y - (m_bodySize / 2);
    m_shape.right = m_shape.left + m_bodySize;
    m_shape.bottom = m_shape.top + m_bodySize;

    m_moveSpeed = 3;

    mb_dirCheck[m_moveDir] = true;
    m_beforeMoveDir = m_moveDir;
    for (int i = 0; i < 4; i++)
    {
        if (mb_dirCheck[m_moveDir] == true) break;
        mb_dirCheck[i] = false;
    }

    for (int i = 0; i < MoveDir::End; i++)
    {
        m_enemyFrame[i] = i * 2;
    }

    m_enemyStatus = EnemyStatus::Create;
    m_frameX = 0;
    m_frameY = 0;
    m_maxFrameX = 3;

    return S_OK;
}

void SpeedTank::Update()
{
    if (m_enemyStatus == EnemyStatus::Create)
    {
        // 시간 정지 아이템 먹었을 때
        if (!m_gameScene->GetIsTimeStop())
        {
            totElapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
            ++m_elapsedCount;
        }
        if (m_elapsedCount > 3)
        {
            m_frameX += m_frameCount;
            if (m_frameX >= m_maxFrameX)
            {
                m_frameCount = -1;
                m_maxFrameX = 0;
            }
            else if (m_frameX <= m_maxFrameX)
            {
                m_frameCount = 1;
                m_maxFrameX = 3;
            }
            m_elapsedCount = 0;
        }

        if (totElapsedCount >= 2.0f)
        {
            m_enemyStatus = EnemyStatus::Alive;
            m_img = ImageManager::GetSingleton()->FindImage("Image/Enemy.bmp");
            m_bodySize = m_img->GetFrameWidth();
            m_frameX = m_enemyFrame[MoveDir::Down];
            m_frameY = (int)EnemyType::Speed;
            m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
            m_elapsedCount = 0;
            totElapsedCount = 0.0f;
        }
    }
    else if (m_enemyStatus == EnemyStatus::Alive)
    {
        // 시간 정지 아이템 먹었을 때
        if (!m_gameScene->GetIsTimeStop())
        {
            // 미사일 딜레이   
            m_fireElapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
            if (m_fireElapsedCount > 4.0f)
            {
                mb_isFire = true;
                m_fireElapsedCount = 0;
            }
            // 시간에 따른 탱크 이미지(탱크 움직임) 프레임 업데이트
            ++m_elapsedCount;
            if (m_elapsedCount % 5 == 0)
            {
                ++m_frameX;
                if (m_frameX > m_maxFrameX)
                {
                    m_frameX -= 2;
                }
            }

            // 탱크 위치 좌표 업데이트
            AutoMove();


            // 타일과 충돌했을 시
            IsCollisionTile();

            // 충돌했을시 방향 전환
            MoveDir dir;
            if (IsCollisionMap(dir))
            {
                switch (dir)
                {
                case MoveDir::Left:		m_pos.x = m_pos.x + (m_tileMap->GetShape().left - m_shape.left); break;
                case MoveDir::Right:	m_pos.x = m_pos.x - (m_shape.right - m_tileMap->GetShape().right); break;
                case MoveDir::Up:	    m_pos.y = m_pos.y + (m_tileMap->GetShape().top - m_shape.top); break;
                case MoveDir::Down:	    m_pos.y = m_pos.y - (m_shape.bottom - m_tileMap->GetShape().bottom); break;
                }

                //RandomDirChange();
            }

            // 시간에 따른 탱크 이동방향 전환
            TimeDirChange();
        }
    }
    else if (m_enemyStatus == EnemyStatus::Dead)
    {
        if (mb_isReady == true)
        {
            m_boomImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Boom_Effect2_Tank.bmp");
            m_bodySize = 0;
            m_shape.left = (long)m_pos.x - (m_bodySize / 2);
            m_shape.top = (long)m_pos.y - (m_bodySize / 2);
            m_shape.right = m_shape.left + m_bodySize;
            m_shape.bottom = m_shape.top + m_bodySize;
            m_frameX = 0;
            m_frameY = 0;
            m_maxFrameX = 4;
            m_frameCount = 1;
            m_boomElapsedCount = 0.0f;
            m_scale = 1.5f;
            totElapsedCount = 0.0f;
            mb_isReady = false;
        }

        totElapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
        m_boomElapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
        if (m_boomElapsedCount > 0.07f)
        {
            m_frameX += m_frameCount;
            if (m_frameX >= m_maxFrameX)
            {
                m_frameCount = -1;
                m_maxFrameX = 0;
            }
            else if (m_frameX <= m_maxFrameX)
            {
                m_frameCount = 1;
                m_maxFrameX = 4;
            }
            m_boomElapsedCount = 0.0f;
        }

        if (totElapsedCount > 0.70f)
        {
            m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Point.bmp");
            m_frameX = 1;
            m_frameY = 0;
            totElapsedCount = 0.0f;
            m_renderScore = true;
            m_enemyStatus = EnemyStatus::End;
        }
    }
    else if (m_renderScore == true)
    {
        if(m_hitByGranade == false)
        {
			totElapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
			if (totElapsedCount > 0.5f)
			{
				m_hitByGranade = true;
			}
        }
        else 
        {
            m_renderScore = false;
            mb_isAlive = false;
        }
    }
}

void SpeedTank::Render(HDC hdc)
{
    //Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);

    if (m_img && m_enemyStatus == EnemyStatus::Create)
    {
        m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y, m_frameX, m_frameY);
    }
    else if (m_img && m_enemyStatus == EnemyStatus::Alive)
    {
        m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y, m_frameX, m_frameY);
    }
    else if (m_boomImage && m_enemyStatus == EnemyStatus::Dead)
    {
        if (m_frameX == 3 || m_frameX == 4) { m_scale = 3.0f; }
        else { m_scale = 2.0f; }
        m_boomImage->Render(hdc, (int)m_pos.x, (int)m_pos.y, m_frameX, m_frameY, m_scale);
    }
    else if (m_img && m_renderScore == true && m_hitByGranade == false)
    {
        m_img->Render(hdc, (int)m_pos.x, (int)m_pos.y, m_frameX, m_frameY, 2.0f);
    }
        
}

