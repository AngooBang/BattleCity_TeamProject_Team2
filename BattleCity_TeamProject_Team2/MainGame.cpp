#include "MainGame.h"
#include "Image.h"
#include "GameScene.h"



HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("���Ӿ�", new GameScene());


	SceneManager::GetSingleton()->ChangeScene("���Ӿ�");

	srand((unsigned int)time(nullptr));
	// Ÿ�̸� ����
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	clickedMousePosY = 0;

	// �����
	backBuffer = new Image;
	int maxSizeX = WIN_SIZE_X > TILEMAPTOOL_SIZE_X ? WIN_SIZE_X : TILEMAPTOOL_SIZE_X;
	int maxSizeY = WIN_SIZE_Y > TILEMAPTOOL_SIZE_Y ? WIN_SIZE_Y : TILEMAPTOOL_SIZE_Y;
	backBuffer->Init("Image/mapImage.bmp", maxSizeX, maxSizeY);

	//for (int i = 0; i < 10; i++)
	//{
	//	enemy[i] = new Enemy;
	//	enemy[i]->Init();
	//	// �迭 Ÿ�ϸʱ��� �ʱⰪ�ٶ� ���� ���Ǵ� ���
	//	POINTFLOAT pos { 100.0f + (i % 5) * 100.0f, 100.0f + (i / 5) * 80.0f };
	//	enemy[i]->SetPos(pos);
	//}
	return S_OK;
}

void MainGame::Update()
{
	// ����ð� (������Ʈ�� ȣ��Ǿ� ���� �ð��� ����)
	// ����ð� - �����ð� = ����ð�

	TimerManager::GetSingleton()->Update();
	SceneManager::GetSingleton()->Update();



	InvalidateRect(g_hWnd, NULL, false);

	// �����ð� = ����ð� (�����ð��� ����)
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
	// Ÿ�̸� ��ü ����
	KillTimer(g_hWnd, 0);
}

