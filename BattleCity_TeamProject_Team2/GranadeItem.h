#pragma once
#include "Item.h"
class GranadeItem : public Item
{
public:
	virtual ~GranadeItem() {}
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

