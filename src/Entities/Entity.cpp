#include "Entity.h"


Entity::Entity(void)
{
	this -> modelMatrix = new float[16];
}


Entity::~Entity(void)
{
	delete colShape;
	delete motionState;
	delete body;
	delete modelMatrix;
}

float* Entity::getModelMatrix()
{
	
	body->getWorldTransform().getOpenGLMatrix(modelMatrix);
	return modelMatrix;
}
/*
void Entity::setRotation(btQuaternion quat)
{
	body->getWorldTransform().setRotation(quat);
}

void Entity::setPosition(btVector3 origin)
{
	body->getWorldTransform().setOrigin(origin);
}
*/