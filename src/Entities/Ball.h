#pragma once
#include "entity.h"

class Ball :
	public Entity
{
public:
	Ball(float x, float z, float forceX, float forceY);
	~Ball(void);
	

private:
	float DEFAULT_RADIUS; 
	float DEFAULT_SPEED;

};

