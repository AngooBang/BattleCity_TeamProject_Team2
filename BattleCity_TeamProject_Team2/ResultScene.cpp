#include "ResultScene.h"
#include "Image.h"
#include "Ammo.h"

HRESULT ResultScene::Init()
{
	//스테이지 넘버 
	//int StageNum = 1;
	StageNum = GameManager::GetSingleton()->GetStageNr();

	//적 숫자 받아오기
	//m_Enemytype[0] = GameManager::GetSingleton()->GetKillCount()->basicTankNr;
	//m_Enemytype[1] = GameManager::GetSingleton()->GetKillCount()->speedTankNr;
	//m_Enemytype[2] = GameManager::GetSingleton()->GetKillCount()->powerTankNr;
	//m_Enemytype[3] = GameManager::GetSingleton()->GetKillCount()->armorTankNr;

	//이미지 불러오기 

	ImageManager::GetSingleton()->DeleteImage("Image/backGround2.bmp");
	ImageManager::GetSingleton()->AddImage("Image/backGround2.bmp", WIN_SIZE_X, WIN_SIZE_Y);


	m_backGround = ImageManager::GetSingleton()->FindImage("Image/backGround2.bmp");

	m_HIScore = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/HISocre.bmp");

	m_Player1 = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Player1.bmp");

	m_PTS = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/PTS.bmp");

	m_TotalScore = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/TotalScore.bmp");

	m_Stage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage_w.bmp");

	m_NumberImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
	/*ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/ScoreNumber.bmp", 40, 14, true, RGB(255, 0, 255));*/
	m_ArrowImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Arrow.bmp");

	m_OrangeNumberImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/ScoreNumber.bmp");

	m_EnemyImg = ImageManager::GetSingleton()->FindImage("Image/Enemy.bmp");


	m_elapseCount = -100;
	m_CalculateEnemytypeNum = 0;
	mb_Calculate = true;

	return S_OK;
}

void ResultScene::Update()
{
	// 스테이지 숫자 갱신
	/*if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F4))
	{
		StageNum++;
		if (StageNum > 9)
			StageNum = 0;
	}*/

	// 탱크 종류 마다 점수 갱신 (탱크 킬할떄마다 스코어 프레임 증가하는 방식)
	if (mb_Calculate == true)
	{
		m_elapseCount++;
		if (m_elapseCount == 15)
		{
			if (m_countofEnemy[m_CalculateEnemytypeNum] != m_Enemytype[m_CalculateEnemytypeNum])
			{
				m_countofEnemy[m_CalculateEnemytypeNum]++;
				m_scoreSum[m_CalculateEnemytypeNum] = m_countofEnemy[m_CalculateEnemytypeNum] * m_enemyScore[m_CalculateEnemytypeNum];
				m_elapseCount = 0;
			}
			else
			{
				if (m_CalculateEnemytypeNum < 3)
				{
					m_CalculateEnemytypeNum++;
				}
				else if (m_CalculateEnemytypeNum == 3)
				{
					mb_Calculate = false;
				}
				m_elapseCount = -75;
			}
		}
	}
	else
	{
		if (GameManager::GetSingleton()->GetStageNr() != GameManager::GetSingleton()->GetMaxStageNr() &&
			GameManager::GetSingleton()->GetPlayerHp() != 0 )
		{
			GameManager::GetSingleton()->SetStageNrPlus(1);
			GameManager::GetSingleton()->ResetKillCount();
			
			Sleep(1000);
			SceneManager::GetSingleton()->ChangeScene("스테이지씬");
		}
		else
		{
			Sleep(1000);
			SceneManager::GetSingleton()->ChangeScene("게임오버씬");
		}
	}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F5))
	//{
	//	m_countofEnemy[0]++;
	//	Calculate(0);
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F6))
	//{
	//	m_countofEnemy[1]++;
	//	Calculate(1);
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F7))
	//{
	//	m_countofEnemy[2]++;
	//	Calculate(2);
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F8))
	//{
	//	m_countofEnemy[3]++;
	//	Calculate(3);
	//}
}

void ResultScene::Render(HDC hdc)
{
	m_backGround->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	m_HIScore->Render(hdc, HISCORE_POS_X, HISCORE_POS_Y);
	m_Stage->Render(hdc, (int)(WIN_SIZE_X / 2.6), WIN_SIZE_Y / 5);
	m_NumberImg->Render(hdc, STAGENUM_POS_X, STAGENUM_POS_Y, StageNum % 5, StageNum / 5);

	for (int k = 0; k < 4; k++)
	{
		m_PTS->Render(hdc, WIN_SIZE_X / 4, (int)(WIN_SIZE_Y * 0.4f + k * 70.0f));
		m_EnemyImg->Render(hdc, WIN_SIZE_X / 3 + 120, WIN_SIZE_Y - 540 + (70 * k), 0, k);
		m_ArrowImg->Render(hdc, WIN_SIZE_X / 3 + 67, WIN_SIZE_Y - 540 + (70 * k));
	}
	m_Player1->Render(hdc, WIN_SIZE_X / 4 - 55, WIN_SIZE_Y / 4);
	m_TotalScore->Render(hdc, WIN_SIZE_X / 3 - 10, (int)(WIN_SIZE_Y * 0.7));

	// 스테이지 종료 후 얻은 최종점수 출력
	RenderCalculate(hdc, m_totScore, WIN_SIZE_X / 5 + 75, WIN_SIZE_Y - 625);

	// 각 탱크별 점수 출력
	for (int i = 0; i <= m_CalculateEnemytypeNum; i++)
	{
		//m_NumberImg->Render(hdc, WIN_SIZE_X / 3 + 30, WIN_SIZE_Y - 540 + (70 * i), m_numFrameX[m_countofEnemy[i]], m_numFrameY[m_countofEnemy[i]]);
		//m_NumberImg->Render(hdc, WIN_SIZE_X / 5 - 10, WIN_SIZE_Y - 540 + (70 * i), 0, 0);
		//if (m_scoreSum[i] != 0)
		//{
		//	m_NumberImg->Render(hdc, WIN_SIZE_X / 5 - 35, WIN_SIZE_Y - 540 + (70 * i), 0, 0);
		//	m_NumberImg->Render(hdc, WIN_SIZE_X / 5 - 60, WIN_SIZE_Y - 540 + (70 * i), m_numFrameX[m_scoreHundredsofDigits[i]], m_numFrameY[m_scoreHundredsofDigits[i]]);
		//	if (m_scoreSum[i] >= 1000)
		//	{
		//		m_NumberImg->Render(hdc, WIN_SIZE_X / 5 - 85, WIN_SIZE_Y - 540 + (70 * i), m_numFrameX[m_scoreThousandofDigits[i]], m_numFrameY[m_scoreThousandofDigits[i]]);
		//	}
		//}
		
		// 탱크 갯수에 따른 점수계산 출력
		RenderCalculate(hdc, m_scoreSum[i], WIN_SIZE_X / 5 - 10, WIN_SIZE_Y - 540, i);

		// 탱크 갯수 출력
		RenderCalculate(hdc, m_countofEnemy[i], WIN_SIZE_X / 3 + 30, WIN_SIZE_Y - 540, i);
	}
	//m_enemySumScoreThousandNumImg[1]->Render(hdc, WIN_SIZE_X / 5 - 85, WIN_SIZE_Y - 470, m_numFrameX[m_scoreThousandofDigits[1]], m_numFrameY[m_scoreThousandofDigits[1]]);
	//m_enemySumScoreHundredsNumImg[1]->Render(hdc, WIN_SIZE_X / 5 - 60, WIN_SIZE_Y - 470, m_numFrameX[m_scoreHundredsofDigits[1]], m_numFrameY[m_scoreHundredsofDigits[1]]);
	//m_enemySumScoreZero1NumImg[1]->Render(hdc, WIN_SIZE_X / 5 - 35, WIN_SIZE_Y - 470, 0, 0);
	//m_enemySumScoreZero2NumImg[1]->Render(hdc, WIN_SIZE_X / 5 - 10, WIN_SIZE_Y - 470, 0, 0);
	//
	//m_enemySumScoreThousandNumImg[2]->Render(hdc, WIN_SIZE_X / 5 - 85, WIN_SIZE_Y - 400, m_numFrameX[m_scoreThousandofDigits[2]], m_numFrameY[m_scoreThousandofDigits[2]]);
	//m_enemySumScoreHundredsNumImg[2]->Render(hdc, WIN_SIZE_X / 5 - 60, WIN_SIZE_Y - 400, m_numFrameX[m_scoreHundredsofDigits[2]], m_numFrameY[m_scoreHundredsofDigits[2]]);
	//m_enemySumScoreZero1NumImg[2]->Render(hdc, WIN_SIZE_X / 5 - 35, WIN_SIZE_Y - 400, 0, 0);
	//m_enemySumScoreZero2NumImg[2]->Render(hdc, WIN_SIZE_X / 5 - 10, WIN_SIZE_Y - 400, 0, 0);
	//
	//m_enemySumScoreThousandNumImg[3]->Render(hdc, WIN_SIZE_X / 5 - 85, WIN_SIZE_Y - 330, m_numFrameX[m_scoreThousandofDigits[3]], m_numFrameY[m_scoreThousandofDigits[3]]);
	//m_enemySumScoreHundredsNumImg[3]->Render(hdc, WIN_SIZE_X / 5 - 60, WIN_SIZE_Y - 330, m_numFrameX[m_scoreHundredsofDigits[3]], m_numFrameY[m_scoreHundredsofDigits[3]]);
	//m_enemySumScoreZero1NumImg[3]->Render(hdc, WIN_SIZE_X / 5 - 35, WIN_SIZE_Y - 330, 0, 0);
	//m_enemySumScoreZero2NumImg[3]->Render(hdc, WIN_SIZE_X / 5 - 10, WIN_SIZE_Y - 330, 0, 0);

	// 탱크 총 갯수 렌더

	if (mb_EnemyCalculateDone == true)
	{
		RenderCalculate(hdc, m_countofEnemy[0]+ m_countofEnemy[1]+ m_countofEnemy[2]+ m_countofEnemy[3], WIN_SIZE_X / 3 + 30, WIN_SIZE_Y - 540);
	}

}

void ResultScene::Release()
{
	m_enemyMgr = nullptr;
}

void ResultScene::RenderCalculate(HDC hdc, int num, int posX, int posY, int CalculateEnemytypeNum)
{
	m_Temp = num;
	while (m_Temp != 0)
	{
		m_Digit = m_Temp % 10;
		m_NumberImg->Render(hdc, posX - (25 * m_TempCount), posY + (70 * CalculateEnemytypeNum), m_numFrameX[m_Digit], m_numFrameY[m_Digit]);
		m_Temp /= 10;
		m_TempCount++;
	}
	m_TempCount = 0;
}
