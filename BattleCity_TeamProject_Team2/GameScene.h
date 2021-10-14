#pragma once
#include "GameEntity.h"

class UIManager;
class Image;

class EnemyManager;
class GameScene : public GameEntity
{
private:
	Image* m_backGround;
	EnemyManager* m_enemyMgr;


	UIManager* m_uiManager;
public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	
	void Release();
};

