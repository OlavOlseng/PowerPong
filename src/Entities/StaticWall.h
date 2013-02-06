#ifndef S_WALL_H
#define S_WALL_H

#include "Entity.h"

class StaticWall :
	public Entity
{
public:
	StaticWall(float width, bool inX, float xPos, float zPos);
	StaticWall(float width, float rotY, float xPos, float zPos);
	~StaticWall(void);

};

#endif