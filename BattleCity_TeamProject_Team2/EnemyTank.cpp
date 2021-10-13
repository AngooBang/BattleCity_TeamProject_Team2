#include "EnemyTank.h"
#include "Image.h"

HRESULT EnemyTank::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/Taeyeon.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    m_backGround = ImageManager::GetSingleton()->FindImage("Image/Taeyeon.bmp");

    ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
    m_img = ImageManager::GetSingleton()->FindImage("Image/Enemy.bmp");

    m_pos.x = WIN_SIZE_X / 2;
    m_pos.y = WIN_SIZE_Y / 2;

    m_bodySize = m_img->GetFrameWidth();

    m_shape.left = m_pos.x - (m_bodySize / 2);
    m_shape.top = m_pos.y - (m_bodySize / 2);
    m_shape.right = m_shape.left + m_bodySize;
    m_shape.bottom = m_shape.top + m_bodySize;

    m_moveSpeed = 3;
    m_moveDir = MoveDir::Left;

    m_elapsedCount = 0;
    m_moveDelay = 70;

    for (int i = 0; i < MoveDir::End; i++)
    {
        m_enemyFrame[i] = i * 2;
    }
    
    m_imgDelay = 5;
    m_frameX = m_enemyFrame[MoveDir::Left];
    m_frameY = 0;
    m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;

    return S_OK;
}

void EnemyTank::Update()
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

void EnemyTank::Render(HDC hdc)
{
    //if (m_backGround)
    //    m_backGround->Render(hdc);

    Rectangle(hdc, m_shape.left, m_shape.top, m_shape.right, m_shape.bottom);

    if (m_img)
        m_img->Render(hdc, m_pos.x, m_pos.y, m_frameX, m_frameY);
}

void EnemyTank::Release()
{
    SAFE_RELEASE(m_backGround);
    SAFE_RELEASE(m_img);
}

void EnemyTank::AutoMove()
{
    // 탱크가 화면과 충돌시 방향전환
    if (m_shape.right >= WIN_SIZE_X)
    {
        m_moveDir = MoveDir::Left;
        m_frameX = m_enemyFrame[MoveDir::Left];
        m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;
    }
    else if (m_shape.left <= 0)
    {
        m_moveDir = MoveDir::Right;
        m_frameX = m_enemyFrame[MoveDir::Right];
        m_maxFrameX = m_enemyFrame[MoveDir::Right] + 1;
    }
    else if (m_shape.top <= 0)
    {
        m_moveDir = MoveDir::Down;
        m_frameX = m_enemyFrame[MoveDir::Down];
        m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
    }
    else if (m_shape.bottom >= WIN_SIZE_Y)
    {
        m_moveDir = MoveDir::Up;
        m_frameX = m_enemyFrame[MoveDir::Up];
        m_maxFrameX = m_enemyFrame[MoveDir::Up] + 1;
    }

    switch (m_moveDir)
    {
    case MoveDir::Left:		m_pos.x -= m_moveSpeed; break;
    case MoveDir::Right:	m_pos.x += m_moveSpeed; break;
    case MoveDir::Up:	    m_pos.y -= m_moveSpeed; break;
    case MoveDir::Down:	    m_pos.y += m_moveSpeed; break;
    }
}
