#pragma once
#include "Item.h"
class TimeItem : public Item
{
private:
	float m_timeStopCount;

public:
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

