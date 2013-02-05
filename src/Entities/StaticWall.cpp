#include "StaticWall.h"


StaticWall::StaticWall(float length, bool inX, float xPos, float zPos)
	: Entity(Entity::STATIC_WALL_ID)
{
	if(inX) 
	{
		this -> colShape = new btBoxShape(btVector3(length/2,4,1));
	}
	else
	{
		this -> colShape = new btBoxShape(btVector3(1,4,length/2));
		
	}
	this -> motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(xPos,2,zPos)));
	this -> mass = 0.0;
	this -> inertia = btVector3(0,0,0);
	this -> colShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI(mass,motionState,colShape,inertia);
	this -> body = new btRigidBody(bodyCI);
	this -> body -> setRestitution(1.0);
	this -> body -> setFriction(0.5);
	this -> body->setRollingFriction(0.3);
	body->setUserPointer(this);
}

StaticWall::StaticWall(float length, float rotY, float xPos, float zPos)
	: Entity(Entity::STATIC_WALL_ID)
{
	this -> colShape = new btBoxShape(btVector3(length/2,4,1));
	this -> motionState = new btDefaultMotionState(btTransform(btQuaternion(0,rotY,0,1), btVector3(xPos,2,zPos)));
	this -> mass = 0.0;
	this -> inertia = btVector3(0,0,0);
	this -> colShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI(mass,motionState,colShape,inertia);
	this -> body = new btRigidBody(bodyCI);
	this -> body -> setRestitution(1.0);
	this -> body -> setFriction(0.0);
	body->setUserPointer(this);
}

StaticWall::~StaticWall(void)
{
}
