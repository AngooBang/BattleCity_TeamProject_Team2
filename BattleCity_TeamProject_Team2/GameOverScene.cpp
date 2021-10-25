#include "GameOverScene.h"
#include "Image.h"

HRESULT GameOverScene::Init()
{
	m_backGround = ImageManager::GetSingleton()->FindImage("Image/backGround2.bmp");
	m_elapsedTime = 0.0f;

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/GameOver.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	m_gameOver = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/GameOver.bmp");

	return S_OK;
}

void GameOverScene::Update()
{
    m_elapsedTime += TimerManager::GetSingleton()->GetDeltaTime();
    if (m_elapsedTime > 4.0f)
    {
		GameManager::GetSingleton()->ResetData();
        SceneManager::GetSingleton()->ChangeScene("Å¸ÀÌÆ²¾À");
    }
}

void GameOverScene::Render(HDC hdc)
{
	m_backGround->Render(hdc);
	m_gameOver->Render(hdc);
}

void GameOverScene::Release()
{
}
