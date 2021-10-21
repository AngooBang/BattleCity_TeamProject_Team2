#pragma once
#include "GameEntity.h"


#define ENEMY_LEFT_POS_X 885
#define ENEMY_LEFT_POS_Y 100

#define PLAYER1_LIFE_POS_X 900
#define PLAYER1_LIFE_POS_Y 400

#define STAGE_FLAG_POS_X 900
#define STAGE_FLAG_POS_Y 600




class Image;
class UIManager : public GameEntity
{
private:
	Image* m_enemyLeft;
	Image* m_p1LifeUI;
	Image* m_numberUI;
	Image* m_stageFlag;


	int m_enemyLeftNum;
	int m_p1LifeNum;
	int m_stageNum;


public:
	virtual HRESULT Init(int m_enemyTotNum);
	virtual void Update(int m_enemyTotNum, int m_enemyNumCount, int m_playerHp);
	virtual void Render(HDC hdc);
	virtual void Release();
};

