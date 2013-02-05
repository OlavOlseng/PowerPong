#include "Block.h"


Block::Block(float x, float y, float z)
	: Entity(Entity::BLOCK_ID)
{
	this -> colShape = new btBoxShape(btVector3(1,1,1));	
	
	this -> motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(x,y,z)));
	this -> mass = 2.0f;
	this -> inertia = btVector3(0,0,0);

	this -> colShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI(mass,motionState,colShape,inertia);
	this -> body = new btRigidBody(bodyCI);
	body->setUserPointer(this);
	this -> body->setRestitution(1.0);
}


Block::Block(float width, float height, float depth, float x, float y, float z)
	: Entity(Entity::BLOCK_ID)

{
	this -> colShape = new btBoxShape(btVector3(width/2,height/2,depth/2));	

	this -> motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(x,y,z)));
	this -> mass = 2.0;
	this -> inertia = btVector3(0,0,0);
	this -> colShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI(mass,motionState,colShape,inertia);
	this -> body = new btRigidBody(bodyCI);
	this -> body -> setRestitution(1.0);
	body->setUserPointer(this);
}

Block::~Block(void)
{
}
