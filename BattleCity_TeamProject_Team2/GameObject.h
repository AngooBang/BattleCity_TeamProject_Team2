#pragma once
#include "GameEntity.h"

class Image;
class GameObject : public GameEntity
{
protected:
	POINTFLOAT m_pos;
	int m_bodySize;
	RECT m_shape;
	float m_moveSpeed;

	Image* m_img;

public:
	void Move();

	inline void SetPos(POINTFLOAT m_pos) { this->m_pos = m_pos; }
	inline POINTFLOAT GetPos() { return this->m_pos; }
	inline void SetMoveSpeed(float m_moveSpeed) { this->m_moveSpeed = m_moveSpeed; }
	inline int GetBodySize() { return this->m_bodySize; }

	GameObject();
	~GameObject();
};

