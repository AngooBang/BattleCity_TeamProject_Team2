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

	// �׽�Ʈ�� ����(���� ���￹��)
	// (���Ŀ� ���ʹ� Ÿ���� ��Ʈ������ ����ȯ��Ų ���� �����ÿ���)
	// (����� ��Ʈ��Ʈ �ڷ����� �Ϲݺ��������� ������ ������ �����)
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

