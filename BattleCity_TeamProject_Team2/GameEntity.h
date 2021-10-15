#pragma once
#include <Windows.h>
#include "Config.h"
#include "CommonFunction.h"

class GameEntity
{
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

