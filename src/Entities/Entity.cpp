#include "Entity.h"


Entity::Entity(EntityID cID)
{
	this -> modelMatrix = new float[16];
	//body -> setUserPointer(this);
	this->cID = cID;
	this->entID = uID;
	uID++;
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
float* Entity::getPosition()
{
	return this -> body -> getWorldTransform().getOrigin();
}

btRigidBody* Entity::getBody()
{
	return body;
}

EntityID Entity::getEntityID()
{
	return entID;
}

ClassID Entity::getClassID()
{
	return this->cID;
}

void Entity::setCollisionHandler(CollisionHandler* h)
{
	this->colHand = h;
}

CollisionHandler* Entity::getCollisionHandler()
{
	return this->colHand;
}


btQuaternion  Entity::getOrientation()
{
	return this->body->getOrientation().normalized();
}
