#include "GameOverScene.h"
#include "Image.h"

HRESULT GameOverScene::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/game_over_screen.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    m_img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/game_over_screen.bmp");
    m_elapsedTime = 0;

    return S_OK;
}

void GameOverScene::Update()
{
    m_elapsedTime += TimerManager::GetSingleton()->GetDeltaTime();

    if (m_elapsedTime > 5.0f)
    {
        //GameManager::GetSingleton()->SetStageNrPlus(1);
        //SceneManager::GetSingleton()->ChangeScene("°ÔÀÓ¾À");
        //SceneManager::GetSingleton()->ChangeScene("Å¸ÀÌÆ²¾À");
    }
}

void GameOverScene::Render(HDC hdc)
{
    m_img->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
}

void GameOverScene::Release()
{
}
