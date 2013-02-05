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


void Entity::setUserPointer(void * ptr){
	this ->body->setUserPointer(ptr);

}
void *  Entity::getUserPointer(){
	
	return this->body->getUserPointer();

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
float * Entity::getPosition()
{
	
	return this -> body -> getWorldTransform().getOrigin();
}

btQuaternion  Entity::getOrientation(){

	return this->body->getOrientation().normalized();

}