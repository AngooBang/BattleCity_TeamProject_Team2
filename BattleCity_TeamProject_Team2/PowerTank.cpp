#include "PowerTank.h"
#include "Image.h"

HRESULT PowerTank::Init(POINTFLOAT pos, EnemyManager* manager)
{
    m_manager = manager;
    ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
    m_img = ImageManager::GetSingleton()->FindImage("Image/Enemy.bmp");

    m_pos.x = pos.x;
    m_pos.y = pos.y;

    m_bodySize = m_img->GetFrameWidth();

    m_shape.left = m_pos.x - (m_bodySize / 2);
    m_shape.top = m_pos.y - (m_bodySize / 2);
    m_shape.right = m_shape.left + m_bodySize;
    m_shape.bottom = m_shape.top + m_bodySize;

    m_moveSpeed = 2;
    m_moveDir = MoveDir::Left;

    for (int i = 0; i < MoveDir::End; i++)
    {
        m_enemyFrame[i] = i * 2;
    }

    m_frameX = m_enemyFrame[MoveDir::Left];
    m_frameY = (int)EnemyType::Power;
    m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;

	return S_OK;
}

void PowerTank::Update()
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
    // 시간에 따른 탱크 이동방향 전환
    if (m_elapsedCount > m_moveDelay)
    {
        int  RandomValue = rand() % 4;
        switch (RandomValue)
        {
        case 0:
            m_moveDir = MoveDir::Left;
            m_frameX = m_enemyFrame[MoveDir::Left];
            m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;
            break;

        case 1:
            m_moveDir = MoveDir::Right;
            m_frameX = m_enemyFrame[MoveDir::Right];
            m_maxFrameX = m_enemyFrame[MoveDir::Right] + 1;
            break;

        case 2:
            m_moveDir = MoveDir::Up;
            m_frameX = m_enemyFrame[MoveDir::Up];
            m_maxFrameX = m_enemyFrame[MoveDir::Up] + 1;
            break;

        case 3:
            m_moveDir = MoveDir::Down;
            m_frameX = m_enemyFrame[MoveDir::Down];
            m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
            break;
        }
        m_elapsedCount = 0;
    }

    // 탱크 위치 좌표 업데이트와 화면과 탱크 충돌 처리
    AutoMove();

    m_shape.left = m_pos.x - (m_bodySize / 2);
    m_shape.top = m_pos.y - (m_bodySize / 2);
    m_shape.right = m_shape.left + m_bodySize;
    m_shape.bottom = m_shape.top + m_bodySize;
}

void PowerTank::Render(HDC hdc)
{
    Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);

    if (m_img)
        m_img->Render(hdc, m_pos.x, m_pos.y, m_frameX, m_frameY);
}

