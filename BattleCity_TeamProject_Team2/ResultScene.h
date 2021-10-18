#pragma once
#include "GameEntity.h"

#define HISCORE_POS_X 480
#define HISCORE_POS_Y 120

#define STAGENUM_POS_X 600
#define STAGENUM_POS_Y 180

class EnemyManager;
class Image;
class ResultScene : public GameEntity
{

private:
	Image* m_backGround;
	Image* m_HIScore;
	Image* m_ScoreNumber;
	Image* m_Player1;
	Image* m_PTS;
	Image* m_TotalScore;
	Image* m_Stage;
	Image* m_StageNumber;

	int StageNum;
	EnemyManager* m_enemyMgr;
	

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

