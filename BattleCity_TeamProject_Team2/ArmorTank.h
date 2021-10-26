#pragma once
#include "EnemyTank.h"

class ArmorTank : public EnemyTank
{
private:

public:
	virtual ~ArmorTank() {}
	virtual HRESULT Init(POINTFLOAT pos) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	ArmorTank(TileMap* tileMap) { m_tileMap = tileMap; }
};

