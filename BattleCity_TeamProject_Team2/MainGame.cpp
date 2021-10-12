#include "MainGame.h"
#include "Image.h"
#include "GameScene.h"



HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("게임씬", new GameScene());


	SceneManager::GetSingleton()->ChangeScene("게임씬");

	srand((unsigned int)time(nullptr));
	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	clickedMousePosY = 0;

	// 백버퍼
	backBuffer = new Image;
	int maxSizeX = WIN_SIZE_X > TILEMAPTOOL_SIZE_X ? WIN_SIZE_X : TILEMAPTOOL_SIZE_X;
	int maxSizeY = WIN_SIZE_Y > TILEMAPTOOL_SIZE_Y ? WIN_SIZE_Y : TILEMAPTOOL_SIZE_Y;
	backBuffer->Init("Image/mapImage.bmp", maxSizeX, maxSizeY);

	//for (int i = 0; i < 10; i++)
	//{
	//	enemy[i] = new Enemy;
	//	enemy[i]->Init();
	//	// 배열 타일맵구조 초기값줄때 자주 사용되는 방법
	//	POINTFLOAT pos { 100.0f + (i % 5) * 100.0f, 100.0f + (i / 5) * 80.0f };
	//	enemy[i]->SetPos(pos);
	//}
	return S_OK;
}

void MainGame::Update()
{
	// 현재시간 (업데이트가 호출되어 들어온 시간을 저장)
	// 현재시간 - 이전시간 = 경과시간

	TimerManager::GetSingleton()->Update();
	SceneManager::GetSingleton()->Update();



	InvalidateRect(g_hWnd, NULL, false);

	// 이전시간 = 현재시간 (이전시간에 저장)
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	SceneManager::GetSingleton()->Render(hBackBufferDC);


	TimerManager::GetSingleton()->Render(hBackBufferDC);

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
	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}

