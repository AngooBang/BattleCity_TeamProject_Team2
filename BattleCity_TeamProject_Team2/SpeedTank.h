#pragma once
#include "EnemyTank.h"

class SpeedTank : public EnemyTank
{
private:

public:
	virtual HRESULT Init(POINTFLOAT pos, EnemyManager* manager) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	SpeedTank(RECT mapShape) { m_mapShape = mapShape; }
	~SpeedTank() {}
};

