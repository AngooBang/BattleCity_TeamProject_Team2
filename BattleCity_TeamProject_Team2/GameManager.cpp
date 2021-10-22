#include "GameManager.h"

void GameManager::Init()
{
	m_killCountNr = new KILL_COUNT;
	m_killCountNr->basicTankNr = 0;
	m_killCountNr->speedTankNr = 0;
	m_killCountNr->powerTankNr = 0;
	m_killCountNr->armorTankNr = 0;
	m_killCountNr->totKillTankNr = 0;

	m_stageNr = 1;
}

void GameManager::Update()
{
}

void GameManager::Render()
{
}

void GameManager::Release()
{
	SAFE_DELETE(m_killCountNr);
}

void GameManager::ResetKillCount()
{
	m_killCountNr->basicTankNr = 0;
	m_killCountNr->speedTankNr = 0;
	m_killCountNr->powerTankNr = 0;
	m_killCountNr->armorTankNr = 0;
	m_killCountNr->totKillTankNr = 0;
}
