#pragma once
#include "Tank.h"

class Image;
class PlayerTank : public Tank
{	
private:
	//map<MoveDir, Image*> m_imageData;

	Image* m_ImageData;

public:
	HRESULT Init();
	void KeyUpdate();
	void Render(HDC hdc);
	
};

