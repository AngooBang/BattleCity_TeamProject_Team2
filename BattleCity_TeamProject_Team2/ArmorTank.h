#pragma once
#include "EnemyTank.h"

class ArmorTank : public EnemyTank
{
private:

public:
	virtual HRESULT Init(POINTFLOAT pos, EnemyManager* manager) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

