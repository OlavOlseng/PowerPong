#pragma once
#include "c:\users\olav\documents\visual studio 2012\projects\powerpong\src\entities\entity.h"
class Ball :
	public Entity
{
public:
	Ball(float radius, float x, float y, float z);
	~Ball(void);
};

