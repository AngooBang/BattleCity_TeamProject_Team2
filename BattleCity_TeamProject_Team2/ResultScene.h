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

	Image* m_enemy[4];
	Image* m_enemyCountNumImg[4];

	Image* m_enemySumScoreThousandNumImg[4];
	Image* m_enemySumScoreHundredsNumImg[4];
	Image* m_enemySumScoreZero1NumImg[4];
	Image* m_enemySumScoreZero2NumImg[4];

	int StageNum;
	int m_countofEnemy[4];
	int m_countOneofDigits[4];
	int m_countTenofDigits[4];

	int m_enemyScore[4] = { 100, 200, 300, 400 };
	int m_scoreSum[4];
	int m_scoreThousandofDigits[4];
	int m_scoreHundredsofDigits[4];
	int m_numFrameX[10] = { 0,1,2,3,4,0,1,2,3,4 };
	int m_numFrameY[10] = { 0,0,0,0,0,1,1,1,1,1 };

	// �׽�Ʈ�� ����(���� ���￹��)
	// (���Ŀ� ���ʹ� Ÿ���� ��Ʈ������ ����ȯ��Ų ���� �����ÿ���)
	// (����� ��Ʈ��Ʈ �ڷ����� �Ϲݺ��������� ������ ������ �����)
	//int m_Enemytype[4] = { 10, 5, 8, 14 };
	int m_Enemytype[4];// = { 1,1,1,1 };

	int m_elapseCount;
	int m_CalculateEnemytypeNum;
	bool mb_Calculate;

	EnemyManager* m_enemyMgr;
	

public:
	virtual ~ResultScene() {}
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void Calculate(int num);
};

