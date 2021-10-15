#include "EnemyTank.h"
#include "EnemyManager.h"
#include "Image.h"

HRESULT EnemyTank::Init(POINTFLOAT pos, EnemyManager* manager)
{
    m_manager = manager;
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
    if(m_img)
        SAFE_RELEASE(m_img);
}

void EnemyTank::AutoMove()
{
    // 탱크가 화면과 충돌시 방향전환
    if (m_shape.right >= m_manager->GetTileMapShape().right)
    {
        m_moveDir = MoveDir::Left;
        m_frameX = m_enemyFrame[MoveDir::Left];
        m_maxFrameX = m_enemyFrame[MoveDir::Left] + 1;
    }
    else if (m_shape.left <= m_manager->GetTileMapShape().left)
    {
        m_moveDir = MoveDir::Right;
        m_frameX = m_enemyFrame[MoveDir::Right];
        m_maxFrameX = m_enemyFrame[MoveDir::Right] + 1;
    }
    else if (m_shape.top <= m_manager->GetTileMapShape().top)
    {
        m_moveDir = MoveDir::Down;
        m_frameX = m_enemyFrame[MoveDir::Down];
        m_maxFrameX = m_enemyFrame[MoveDir::Down] + 1;
    }
    else if (m_shape.bottom >= m_manager->GetTileMapShape().bottom)
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
