#pragma once
#include "EnemyTank.h"

class PowerTank : public EnemyTank
{
private:

public:
	virtual HRESULT Init(POINTFLOAT pos) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	PowerTank(RECT mapShape) { m_mapShape = mapShape; }
	~PowerTank() {}
};

