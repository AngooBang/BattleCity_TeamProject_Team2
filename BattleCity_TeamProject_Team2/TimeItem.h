#pragma once
#include "Item.h"
class TimeItem : public Item
{
private:
	bool mb_isActive = false;
	float m_timeStopCount{};

public:
	virtual ~TimeItem() {}
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

