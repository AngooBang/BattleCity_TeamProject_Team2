#pragma once
#include "EnemyTank.h"

class BasicTank : public EnemyTank
{
private:

public:
	virtual HRESULT Init(POINTFLOAT pos) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

};

