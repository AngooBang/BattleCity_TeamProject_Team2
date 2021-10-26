#include "StageScene.h"
#include "Image.h"


HRESULT StageScene::Init()
{
	m_pos.x = WIN_SIZE_X / 2;
	m_pos.y = -(WIN_SIZE_Y / 2);
	m_pos2.y = WIN_SIZE_Y + WIN_SIZE_Y / 2;
	m_moveSpeed = 15;
	m_elapsedTime = 0;
	
	m_stageNr = GameManager::GetSingleton()->GetStageNr();

	ImageManager::GetSingleton()->DeleteImage("Image/backGround2.bmp");
	ImageManager::GetSingleton()->AddImage("Image/backGround2.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	m_backGround2 = ImageManager::GetSingleton()->FindImage("Image/backGround2.bmp");

	ImageManager::GetSingleton()->AddImage("Image/backGround.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	m_backGround = ImageManager::GetSingleton()->FindImage("Image/backGround.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage.bmp", 111, 21);
	m_stage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 120, 42, 5, 2);
	m_stageNumber = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

	return S_OK;
}

void StageScene::AutoMove()
{
	m_pos.y += m_moveSpeed;
	m_pos2.y -= m_moveSpeed;

	if (m_pos.y && m_pos2.y == WIN_SIZE_Y / 2)
		m_moveSpeed = 0;
}

void StageScene::Update()
{
	AutoMove();
	if (m_moveSpeed == 0)
	{
		m_elapsedTime += TimerManager::GetSingleton()->GetDeltaTime();
		if (m_elapsedTime >= 3.0f)
		{
			SceneManager::GetSingleton()->ChangeScene("°ÔÀÓ¾À");
		}
	}
}

void StageScene::Render(HDC hdc)
{
	m_backGround2->Render(hdc);
	m_backGround->Render(hdc, m_pos.x, m_pos.y);
	m_backGround->Render(hdc, m_pos.x, m_pos2.y);
	if (m_moveSpeed == 0) 
	{
		m_stage->Render(hdc, WIN_SIZE_X / 2 - 20, WIN_SIZE_Y / 2);
		m_stageNumber->Render(hdc, WIN_SIZE_X / 2 + 150, WIN_SIZE_Y / 2 + 10, 
							m_stageNumX[m_stageNr % 10], m_stageNumY[m_stageNr % 10]);
	}
}

void StageScene::Release()
{
}

