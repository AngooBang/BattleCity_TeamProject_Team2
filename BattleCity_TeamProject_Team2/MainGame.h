#pragma once
#include "Config.h"
#include "GameEntity.h"



// �츮�� ������ ���� ����
class Image;
class MainGame : public GameEntity
{
private:
	// Ÿ�̸�
	HANDLE hTimer = nullptr;

	int clickedMousePosX = 0;
	int clickedMousePosY = 0;

	// �����
	Image* backBuffer = nullptr;

public:
	virtual ~MainGame() {}
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// �����ε�
	void Release();

};
