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
	virtual HRESULT Init(int m_enemyTotNum);
	virtual void Update(int m_enemyTotNum, int m_enemyNumCount);
	virtual void Render(HDC hdc);
	virtual void Release();
};

