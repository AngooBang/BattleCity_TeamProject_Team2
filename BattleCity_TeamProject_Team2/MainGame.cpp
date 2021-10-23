#include "MainGame.h"
#include "Image.h"
#include "GameScene.h"
#include "ResultScene.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	GameManager::GetSingleton()->Init();
	

	SceneManager::GetSingleton()->AddScene("게임씬", new GameScene());
	SceneManager::GetSingleton()->AddScene("결과씬", new ResultScene());


	SceneManager::GetSingleton()->ChangeScene("결과씬");

	srand((unsigned int)time(nullptr));
	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// 백버퍼
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

	TimerManager::GetSingleton()->Render(hBackBufferDC);
	
	char text[200];
	wsprintf(text, "MousePosX : %d", g_ptMouse.x);
	TextOut(hBackBufferDC, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", g_ptMouse.y);
	TextOut(hBackBufferDC, 200, 40, text, strlen(text));

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TimerManager::GetSingleton()->Release();
	TimerManager::GetSingleton()->ReleaseSingleton();

	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	SceneManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->ReleaseSingleton();

	GameManager::GetSingleton()->Release();
	GameManager::GetSingleton()->ReleaseSingleton();

	KillTimer(g_hWnd, 0);
}

