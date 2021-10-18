#include "EnemyTank.h"
#include "EnemyManager.h"
#include "Image.h"

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

bool EnemyTank::IsCollisionMap()
{
    // 탱크가 화면과 충돌시 방향전환

    if (m_shape.right > m_mapShape.right || m_shape.left < m_mapShape.left
        || m_shape.top < m_mapShape.top || m_shape.bottom > m_mapShape.bottom)
    {
        return true;
    }

    return false;
}
