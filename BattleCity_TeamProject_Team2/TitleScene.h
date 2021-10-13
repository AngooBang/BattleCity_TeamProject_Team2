#pragma once
#include "GameEntity.h"
class TitleScene : public GameEntity
{
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

