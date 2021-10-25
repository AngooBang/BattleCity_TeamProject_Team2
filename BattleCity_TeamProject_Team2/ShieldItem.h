#pragma once
#include "Item.h"
class ShieldItem : public Item
{
public:
	virtual ~ShieldItem() {}
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};