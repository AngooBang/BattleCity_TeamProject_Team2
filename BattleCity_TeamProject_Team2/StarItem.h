#pragma once
#include "Item.h"
class StarItem : public Item
{
public:
	virtual ~StarItem() {}
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

