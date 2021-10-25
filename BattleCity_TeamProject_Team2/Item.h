#pragma once
#include "GameObject.h"

class Image;
class Tank;
class GameScene;
class Item : public GameObject
{
protected:
	Image* m_img;
	float m_elapsedCount;
	int m_showTimeCount;
	
	bool mb_isAlive;
	bool mb_isShow;


	GameScene* m_gameScene;




public:
	virtual ~Item() {}
	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release();

	void CountShow();
	bool CheckCollision();


	inline bool GetIsAlive() { return mb_isAlive; }
	inline void SetIsAlive(bool isAlive) { this->mb_isAlive = isAlive; }


	void SetGameScene(GameScene* gamescene) { this->m_gameScene = gamescene; }
};

