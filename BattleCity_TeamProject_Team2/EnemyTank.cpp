#include "EnemyTank.h"
#include "Image.h"

HRESULT EnemyTank::Init(POINTFLOAT pos)
{
    ImageManager::GetSingleton()->AddImage("Image/Taeyeon.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    m_backGround = ImageManager::GetSingleton()->FindImage("Image/Taeyeon.bmp");

    return S_OK;
}

void EnemyTank::Update()
{
  
}

void EnemyTank::Render(HDC hdc)
{
    //if (m_backGround)
    //    m_backGround->Render(hdc);
}

void EnemyTank::Release()
{
    if(m_backGround) SAFE_RELEASE(m_backGround);
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
