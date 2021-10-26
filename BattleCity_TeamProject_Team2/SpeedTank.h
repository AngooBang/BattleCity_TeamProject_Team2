#pragma once
#include "EnemyTank.h"

class SpeedTank : public EnemyTank
{
private:

public:
	virtual HRESULT Init(POINTFLOAT pos) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	SpeedTank(TileMap* tileMap) { m_tileMap = tileMap; }
	~SpeedTank() {}
};

