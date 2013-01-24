#pragma once
#include "entity.h"
class Ball :
	public Entity
{
public:
	Ball(float radius, float x, float y, float z);
	~Ball(void);
};

