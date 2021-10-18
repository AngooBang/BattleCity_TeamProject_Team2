#pragma once
#include "EnemyTank.h"

class BasicTank : public EnemyTank
{
private:


public:
	virtual HRESULT Init(POINTFLOAT pos, EnemyManager* manager) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	BasicTank(RECT mapShape) {m_mapShape = mapShape; }
	~BasicTank() {}
};

