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
	return S_OK;
}

void ResultScene::Update()
{
// 스테이지 숫자 갱신
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F5))
	{
		StageNum++;
		if (StageNum > 9)
			StageNum = 0;
	}
// 탱크 종류 마다 점수 갱신 (탱크 킬할떄마다 스코어 프레임 증가하는 방식)

}

void ResultScene::Render(HDC hdc)
{

	m_backGround->Render(hdc); 
	m_HIScore->Render(hdc, HISCORE_POS_X, HISCORE_POS_Y);
	m_Stage->Render(hdc, WIN_SIZE_X / 2.6 ,WIN_SIZE_Y / 5);
	m_StageNumber->Render(hdc, STAGENUM_POS_X, STAGENUM_POS_Y, StageNum % 5, StageNum / 5);
	for (int k = 0; k < 4; k++)
	{
		m_PTS->Render(hdc, WIN_SIZE_X / 4, WIN_SIZE_Y * 0.4 + k * 70);
	}
	m_Player1->Render(hdc, WIN_SIZE_X / 4 - 55 , WIN_SIZE_Y / 4);
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
