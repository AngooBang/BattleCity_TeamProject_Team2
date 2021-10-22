#pragma once
#include "Item.h"
class ShieldItem : public Item
{
public:
	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};