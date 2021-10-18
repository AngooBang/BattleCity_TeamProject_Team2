#include "UIManager.h"
#include "Image.h"

HRESULT UIManager::Init(int m_enemyTotNum)
{
	m_enemyLeft = ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Icon_Enemy.bmp", 15, 15);
	m_enemyLeftNum = m_enemyTotNum;
	return S_OK;
}

void UIManager::Update(int m_enemyTotNum, int m_enemyNumCount)
{
	m_enemyLeftNum = m_enemyTotNum;
	m_enemyLeftNum -= m_enemyNumCount;
	/*if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
	{
		m_enemyLeftNum--;

		if (m_enemyLeftNum < 0)
		{
			m_enemyLeftNum = 20;
		}
	}*/
}

void UIManager::Render(HDC hdc)
{
	for (int i = 0; i < m_enemyLeftNum; i++)
	{
		m_enemyLeft->Render(hdc, ENEMY_LEFT_POS_X + (i % 2) * m_enemyLeft->GetWidth(), ENEMY_LEFT_POS_Y + (i / 2) * m_enemyLeft->GetHeight());
	}

}

void UIManager::Release()
{

	SAFE_RELEASE(m_enemyLeft);
}
