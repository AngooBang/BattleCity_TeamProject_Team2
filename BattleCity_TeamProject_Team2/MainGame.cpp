#include "MainGame.h"
#include "Image.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "GameOverScene.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	GameManager::GetSingleton()->Init();
	

	SceneManager::GetSingleton()->AddScene("Ÿ??Ʋ??", new TitleScene());
	SceneManager::GetSingleton()->AddScene("??????????", new StageScene());
	SceneManager::GetSingleton()->AddScene("???Ӿ?", new GameScene());
	SceneManager::GetSingleton()->AddScene("??????", new ResultScene());
	SceneManager::GetSingleton()->AddScene("???ӿ?????", new GameOverScene());

	SceneManager::GetSingleton()->ChangeScene("Ÿ??Ʋ??");
	 
	srand((unsigned int)time(nullptr));
	// Ÿ?̸? ????
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// ??????
	backBuffer = new Image;
	backBuffer->Init("Image/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	return S_OK;
}

void MainGame::Update()
{
	TimerManager::GetSingleton()->Update();
	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	PatBlt(hBackBufferDC, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, WHITENESS);

	SceneManager::GetSingleton()->Render(hBackBufferDC);

	//TimerManager::GetSingleton()->Render(hBackBufferDC);
	
	/*char text[200];
	wsprintf(text, "MousePosX : %d", g_ptMouse.x);
	TextOut(hBackBufferDC, 200, 10, text, (int)strlen(text));

	wsprintf(text, "MousePosY : %d", g_ptMouse.y);
	TextOut(hBackBufferDC, 200, 40, text, (int)strlen(text));*/

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TimerManager::GetSingleton()->Release();

	ImageManager::GetSingleton()->Release();

	KeyManager::GetSingleton()->Release();

	SceneManager::GetSingleton()->Release();

	GameManager::GetSingleton()->Release();

	KillTimer(g_hWnd, 0);
}

