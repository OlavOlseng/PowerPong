#pragma once
#include "Entity.h"

class Plane :
	public Entity
{
public:
	Plane(btVector3* normal, btVector3* origin);
	~Plane(void);

};

