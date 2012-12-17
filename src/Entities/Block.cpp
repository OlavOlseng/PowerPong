#include "Block.h"


Block::Block(int width, float x, float y, float z)
{
	this -> colShape = new btBoxShape(btVector3(width/2,1,1));	
	this -> motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(x,y,z)));
	this -> mass = 1;
	this -> inertia = btVector3(0,0,0);
	this -> colShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI(mass,motionState,colShape,inertia);
	this -> body = new btRigidBody(bodyCI);
}

Block::~Block(void)
{
}

