#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
	delete colShape;
	delete motionState;
	delete body;
}

btMotionState* Entity::getMotionState()
{
	return this -> motionState;
}