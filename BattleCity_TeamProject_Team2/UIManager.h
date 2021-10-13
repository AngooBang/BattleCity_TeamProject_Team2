#pragma once
#include "GameEntity.h"


#define ENEMY_LEFT_POS_X 900
#define ENEMY_LEFT_POS_Y 100




class Image;
class UIManager : public GameEntity
{
private:
	Image* m_enemyLeft;


	int m_enemyLeftNum;


public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

