#include "ResultScene.h"
#include "Image.h"

HRESULT ResultScene::Init()
{
	//스테이지 넘버 
	int StageNum = 1;

	//이미지 불러오기 
	ImageManager::GetSingleton()->AddImage("Image/backGround2.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	m_backGround = ImageManager::GetSingleton()->FindImage("Image/backGround2.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/HISocre.bmp", 470, 50, true, RGB(255, 0, 255));
	m_HIScore = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/HISocre.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Player1.bmp", 230, 40, true, RGB(255, 0, 255));
	m_Player1 = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Player1.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/PTS.bmp", 90, 40, true, RGB(255, 0, 255));
	m_PTS = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/PTS.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/TotalScore.bmp", 360, 40, true, RGB(255, 0, 255));
	m_TotalScore = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/TotalScore.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage_w.bmp", 111, 21, true, RGB(255, 0, 255));
	m_Stage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage_w.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number_w.bmp", 120, 42, 5, 2, true, RGB(255, 0, 255));
	m_StageNumber = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
	/*ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/ScoreNumber.bmp", 40, 14, true, RGB(255, 0, 255));*/

	ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));

	for (int i = 0; i < 4; i++)
	{
		m_enemy[i] = ImageManager::GetSingleton()->FindImage("Image/Enemy.bmp");

		m_enemyCountNumImg[i] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");

		m_enemySumScoreThousandNumImg[i] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
		m_enemySumScoreHundredsNumImg[i] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
		m_enemySumScoreZero1NumImg[i] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
		m_enemySumScoreZero2NumImg[i] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
	}

	m_elapseCount = -100;
	m_CalculateEnemytypeNum = 0;
	mb_Calculate = true;

	return S_OK;
}

void ResultScene::Update()
{
// 스테이지 숫자 갱신
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F4))
	{
		StageNum++;
		if (StageNum > 9)
			StageNum = 0;
	}
// 탱크 종류 마다 점수 갱신 (탱크 킬할떄마다 스코어 프레임 증가하는 방식)
		if(mb_Calculate == true)
		{
			m_elapseCount++;
			if (m_elapseCount == 15)
			{
				if (m_countofEnemy[m_CalculateEnemytypeNum] != m_Enemytype[m_CalculateEnemytypeNum])
				{
					m_countofEnemy[m_CalculateEnemytypeNum]++;
					Calculate(m_CalculateEnemytypeNum);
					m_elapseCount = 0;
				}
				else
				{
					if (m_CalculateEnemytypeNum < 3)
					{
						m_CalculateEnemytypeNum++;
					}					
					else
					{
						mb_Calculate = false;
					}
					m_elapseCount = -75;
				}
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
	m_backGround->Render(hdc);
	m_backGround->Render(hdc); 
	m_Stage->Render(hdc, WIN_SIZE_X / 2.6, WIN_SIZE_Y / 5);
	m_StageNumber->Render(hdc, STAGENUM_POS_X, STAGENUM_POS_Y, StageNum % 5, StageNum / 5);
	m_Stage->Render(hdc, WIN_SIZE_X / 2.6 ,WIN_SIZE_Y / 5);
	m_StageNumber->Render(hdc, STAGENUM_POS_X, STAGENUM_POS_Y, StageNum % 5, StageNum / 5);
	for (int k = 0; k < 4; k++)
	{
		m_PTS->Render(hdc, WIN_SIZE_X / 4, WIN_SIZE_Y * 0.4 + k * 70);
		m_enemy[k]->Render(hdc, WIN_SIZE_X / 3 + 120, WIN_SIZE_Y - 540 + (70 * k), 0, k);
	}

	for (int i = 0; i <= m_CalculateEnemytypeNum; i++)
	{
		m_enemyCountNumImg[i]->Render(hdc, WIN_SIZE_X / 3 + 30, WIN_SIZE_Y - 540 + (70 * i), m_numFrameX[m_countofEnemy[i]], m_numFrameY[m_countofEnemy[i]]);
		m_enemySumScoreZero2NumImg[i]->Render(hdc, WIN_SIZE_X / 5 - 10, WIN_SIZE_Y - 540 + (70 * i), 0, 0);
		if (m_scoreSum[i] != 0)
		{
			m_enemySumScoreZero1NumImg[i]->Render(hdc, WIN_SIZE_X / 5 - 35, WIN_SIZE_Y - 540 + (70 * i), 0, 0);
			m_enemySumScoreHundredsNumImg[i]->Render(hdc, WIN_SIZE_X / 5 - 60, WIN_SIZE_Y - 540 + (70 * i), m_numFrameX[m_scoreHundredsofDigits[i]], m_numFrameY[m_scoreHundredsofDigits[i]]);
			if (m_scoreSum[i] >= 1000)
			{
				m_enemySumScoreThousandNumImg[i]->Render(hdc, WIN_SIZE_X / 5 - 85, WIN_SIZE_Y - 540 + (70 * i), m_numFrameX[m_scoreThousandofDigits[i]], m_numFrameY[m_scoreThousandofDigits[i]]);
			}
		}
	
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
	//if (m_Rendering[0] * m_Rendering[1] * m_Rendering[2] * m_Rendering[3])
	//{

	//}

	m_TotalScore->Render(hdc, WIN_SIZE_X / 3 - 10, WIN_SIZE_Y * 0.7);

}

void ResultScene::Release()
{
	//SAFE_RELEASE(m_backGround);
	//SAFE_RELEASE(m_HIScore);
	//SAFE_RELEASE(m_ScoreNumber);
	//SAFE_RELEASE(m_Player1);
	//SAFE_RELEASE(m_PTS);
	//SAFE_RELEASE(m_TotalScore);
	//SAFE_RELEASE(m_Stage);
	//SAFE_RELEASE(m_StageNumber);
}

void ResultScene::Calculate(int num)
{
	m_scoreSum[num] = m_countofEnemy[num] * m_enemyScore[num];
	m_scoreThousandofDigits[num] = m_scoreSum[num] / 1000;
	m_scoreHundredsofDigits[num] = (m_scoreSum[num] - (1000 * m_scoreThousandofDigits[num])) / 100;
}
