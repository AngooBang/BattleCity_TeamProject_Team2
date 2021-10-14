#pragma once
#include "GameEntity.h"

class Image;
class ResultScene : public GameEntity
{

private:
	Image* m_backGround;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

