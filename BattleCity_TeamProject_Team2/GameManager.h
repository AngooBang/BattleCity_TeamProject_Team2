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

	int m_stageNr = 0;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	inline void SetStageNrPlus(int num) { this->m_stageNr += num; }
	inline int GetStageNr() { return m_stageNr; }

	inline LPKILL_COUNT GetKillCount() { return m_killCountNr; }

	void ResetKillCount();

	/*inline void SetKillNrBasic(int num) { this->m_killCountNr->basicTankNr += num; }
	inline int GetKillNrBasic() { return m_killCountNr->basicTankNr; }

	inline void SetKillNrSpeed(int num) { this->m_killCountNr->SpeedTankNr += num; }
	inline int GetKillNrSpeed() { return m_killCountNr->SpeedTankNr; }

	inline void SetKillNrPower(int num) { this->m_killCountNr->PowerTankNr += num; }
	inline int GetKillNrPower() { return m_killCountNr->PowerTankNr; }

	inline void SetKillNrArmor(int num) { this->m_killCountNr->ArmorTankNr += num; }
	inline int GetKillNrArmor() { return m_killCountNr->ArmorTankNr; }*/

};

