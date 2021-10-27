#include "UIManager.h"
#include "Image.h"

HRESULT UIManager::Init(int m_enemyTotNum)
{
	m_enemyLeft = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Icon_Enemy.bmp");

	m_p1LifeUI = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/player1Life.bmp");
	
	m_numberUI = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

	m_stageFlag = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/StageFlag.bmp");
	
	m_enemyLeftNum = m_enemyTotNum;

	m_stageNum = GameManager::GetSingleton()->GetStageNr();
	return S_OK;
}

void UIManager::Update(int m_enemyTotNum, int m_enemyNumCount, int m_playerHp)
{
	m_enemyLeftNum = m_enemyTotNum;
	m_enemyLeftNum -= m_enemyNumCount;

	m_playerLife = m_playerHp;
}

void UIManager::Render(HDC hdc)
{
	for (int i = 0; i < m_enemyLeftNum; i++)
	{
		m_enemyLeft->Render(hdc, ENEMY_LEFT_POS_X + (i % 2) * m_enemyLeft->GetWidth(), ENEMY_LEFT_POS_Y + (i / 2) * m_enemyLeft->GetHeight());
	}
	m_p1LifeUI->Render(hdc, PLAYER1_LIFE_POS_X, PLAYER1_LIFE_POS_Y);
	m_numberUI->Render(hdc, PLAYER1_LIFE_POS_X + 80, PLAYER1_LIFE_POS_Y + 30, m_playerLife % 5, m_playerLife / 5);
	m_stageFlag->Render(hdc, STAGE_FLAG_POS_X, STAGE_FLAG_POS_Y);
	m_numberUI->Render(hdc, STAGE_FLAG_POS_X + 80, STAGE_FLAG_POS_Y + 50, m_stageNum % 5, m_stageNum / 5);
}

void UIManager::Release()
{
	//SAFE_RELEASE(m_enemyLeft);
	//SAFE_RELEASE(m_p1LifeUI);
	//SAFE_RELEASE(m_numberUI);
	//SAFE_RELEASE(m_stageFlag);
}
