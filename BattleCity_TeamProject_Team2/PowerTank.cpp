#include "PowerTank.h"
#include "Image.h"

HRESULT PowerTank::Init(POINTFLOAT pos)
{
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Spawn_Effect2.bmp",
        256, 64, 4, 1, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
    m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Spawn_Effect2.bmp");

    m_pos.x = pos.x;
    m_pos.y = pos.y;

    m_bodySize = 0;

    m_shape.left = m_pos.x - (m_bodySize / 2);
    m_shape.top = m_pos.y - (m_bodySize / 2);
    m_shape.right = m_shape.left + m_bodySize;
    m_shape.bottom = m_shape.top + m_bodySize;

    m_moveSpeed = 2;

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

void PowerTank::Update()
{
    if (m_enemyStatus == EnemyStatus::Create)
    {
        totElapsedCount += TimerManager::GetSingleton()->GetDeltaTime();
        ++m_elapsedCount;
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
            m_frameY = (int)EnemyType::Power;
            m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
            m_elapsedCount = 0;
        }
    }

    if (m_enemyStatus == EnemyStatus::Alive)
    {
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

        // 충돌했을시 방향 전환
        if (IsCollisionMap())
        {
            switch (m_moveDir)
            {
            case MoveDir::Left:		m_pos.x = m_pos.x + (m_mapShape.left - m_shape.left); break;
            case MoveDir::Right:	m_pos.x = m_pos.x - (m_shape.right - m_mapShape.right); break;
            case MoveDir::Up:	    m_pos.y = m_pos.y + (m_mapShape.top - m_shape.top); break;
            case MoveDir::Down:	    m_pos.y = m_pos.y - (m_shape.bottom - m_mapShape.bottom); break;
            }

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

        // 시간에 따른 탱크 이동방향 전환
        if (m_elapsedCount > m_moveDelay)
        {
            int  RandomValue = rand() % 4;
            switch (RandomValue)
            {
            case 0:
                m_moveDir = MoveDir::Left;
                mb_dirCheck[m_beforeMoveDir] = false;
                mb_dirCheck[m_moveDir] = true;
                m_beforeMoveDir = m_moveDir;

                m_frameX = m_enemyFrame[MoveDir::Left];
                m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;
                break;

            case 1:
                m_moveDir = MoveDir::Right;
                mb_dirCheck[m_beforeMoveDir] = false;
                mb_dirCheck[m_moveDir] = true;
                m_beforeMoveDir = m_moveDir;

                m_frameX = m_enemyFrame[MoveDir::Right];
                m_maxFrameX = m_enemyFrame[MoveDir::Right] + 1;
                break;

            case 2:
                m_moveDir = MoveDir::Up;
                mb_dirCheck[m_beforeMoveDir] = false;
                mb_dirCheck[m_moveDir] = true;
                m_beforeMoveDir = m_moveDir;

                m_frameX = m_enemyFrame[MoveDir::Up];
                m_maxFrameX = m_enemyFrame[MoveDir::Up] + 1;
                break;

            case 3:
                m_moveDir = MoveDir::Down;
                mb_dirCheck[m_beforeMoveDir] = false;
                mb_dirCheck[m_moveDir] = true;
                m_beforeMoveDir = m_moveDir;

                m_frameX = m_enemyFrame[MoveDir::Down];
                m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
                break;
            }
            m_elapsedCount = 0;
        }

    }
}

void PowerTank::Render(HDC hdc)
{
    Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);

    if (m_img && m_enemyStatus == EnemyStatus::Create)
        m_img->Render(hdc, m_pos.x, m_pos.y, m_frameX, m_frameY);

    if (m_img && m_enemyStatus == EnemyStatus::Alive)
        m_img->Render(hdc, m_pos.x, m_pos.y, m_frameX, m_frameY);
}

void PowerTank::Release()
{
    if (m_img)  SAFE_RELEASE(m_img);
}
