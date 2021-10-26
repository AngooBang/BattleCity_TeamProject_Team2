#pragma once
#include "Config.h"
#include "Singleton.h"

	typedef struct KillCountNr
	{
		int basicTankNr;
		int speedTankNr;
		int powerTankNr;
		int armorTankNr;
		int totKillTankNr;
	}KILL_COUNT, *LPKILL_COUNT;

class GameManager : public Singleton<GameManager>
{
private:

	LPKILL_COUNT m_killCountNr = nullptr;

	int m_stageNr = 1;
	int m_maxStageNr = 2;

	int m_playerHP = 5;
	int m_playerFrameY = 0;

	int m_totScore = 0;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	inline void SetTotScore(int num) { this->m_totScore += num; }
	inline int GetTotScore() { return m_totScore; }

	inline void SetStageNrPlus(int num) { this->m_stageNr += num; }
	inline int GetStageNr() { return m_stageNr; }

	inline int GetMaxStageNr() { return m_maxStageNr; }

	inline void SetPlayerHp(int playerHp) { this->m_playerHP = playerHp; }
	inline int GetPlayerHp() { return m_playerHP; }

	inline void SetPlayerFrameY(int playerFrameY) { this->m_playerFrameY = playerFrameY;}
	inline int GetPlayerFrameY() { return m_playerFrameY; }

	inline LPKILL_COUNT GetKillCount() { return m_killCountNr; }

	inline void TotKillTankNrCalculation(int num) { this->m_killCountNr->totKillTankNr += num; }

	void ResetKillCount();
	void ResetData();

};

