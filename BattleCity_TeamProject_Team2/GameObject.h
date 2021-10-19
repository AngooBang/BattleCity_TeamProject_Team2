#pragma once
#include "GameEntity.h"

class GameObject : public GameEntity
{
protected:
	POINTFLOAT m_pos;
	int m_bodySize;
	RECT m_shape;
	float m_moveSpeed;

	TankType m_type;


public:

	inline void SetPos(POINTFLOAT m_pos) { this->m_pos = m_pos; }
	inline POINTFLOAT GetPos() { return this->m_pos; }
	inline void SetMoveSpeed(float m_moveSpeed) { this->m_moveSpeed = m_moveSpeed; }
	
	inline int GetBodySize() { return this->m_bodySize; }
	inline void SetBodySize(int bodySize) { this->m_bodySize = bodySize; }
	
	inline RECT GetShape() { return this->m_shape; }
	inline void SetShape(RECT shape) { this->m_shape = shape; }


	inline TankType GetTankType() { return m_type; }

	GameObject();
	~GameObject();
};

