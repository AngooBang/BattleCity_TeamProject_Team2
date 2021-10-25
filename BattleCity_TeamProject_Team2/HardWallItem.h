#pragma once
#include "Item.h"

class TileMap;
class HardWallItem : public Item
{
private:
	TileMap* m_tileMap;

	bool mb_isActive;
	float m_hardWallCount;

public:
	virtual ~HardWallItem() {}
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetHardWall();
	void ResetHardWall();
};