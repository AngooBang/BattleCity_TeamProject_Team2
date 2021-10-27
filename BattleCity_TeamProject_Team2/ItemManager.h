#pragma once
#include "GameEntity.h"

class Item;
class Tank;
class GameScene;
class ItemManager : public GameEntity
{
private:
	vector<Item*> m_vecItems{};
	Item* m_item = nullptr;
	GameScene* m_gameScene = nullptr;

public:
	virtual ~ItemManager() {}
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AddItem();



	void SetGameScene(GameScene* gamescene) { this->m_gameScene = gamescene; }
};

