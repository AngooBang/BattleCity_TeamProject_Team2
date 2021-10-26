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
	Image* m_NumberImg;
	Image* m_OrangeNumberImg;
	Image* m_EnemyImg;
	Image* m_ArrowImg;

	int StageNum;
	int m_countofEnemy[4];

	int m_enemyScore[4] = { 100, 200, 300, 400 };
	int m_scoreSum[4];
	int m_numFrameX[10] = { 0,1,2,3,4,0,1,2,3,4 };
	int m_numFrameY[10] = { 0,0,0,0,0,1,1,1,1,1 };

	// 테스트용 변수(추후 지울예정)
	// (추후엔 에너미 타입을 인트형으로 형변환시킨 값을 가져올예정)
	// (현재는 스트럭트 자료형에 일반변수형으로 적들의 정보가 저장됨)
	int m_Enemytype[4] = { 10, 5, 8, 14 };
	int m_totScore = 12030;
	//int m_Enemytype[4];

	int m_Temp;
	int m_Digit;
	int m_TempCount;

	int m_elapseCount;
	int m_CalculateEnemytypeNum;
	bool mb_Calculate;
	bool mb_EnemyCalculateDone = false;

	EnemyManager* m_enemyMgr;
	

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void RenderCalculate(HDC hdc, int num, int posX, int posY, int CalculateEnemytypeNum = 0);
};

