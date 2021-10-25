#pragma once
#include "Item.h"
class LifeItem : public Item
{
public:
	virtual ~LifeItem() {}
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};