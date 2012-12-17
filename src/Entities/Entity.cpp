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

float Entity::getY()
{
	this -> motionState -> getWorldTransform(trans);
	return trans.getOrigin().getY();

}