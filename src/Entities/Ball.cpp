#include "Ball.h"


Ball::Ball(float radius, float x, float y, float z)
{
	this -> colShape = new btSphereShape(radius);
	this -> motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(x,y,z)));
	this -> mass = 5.0f;
	this -> inertia = btVector3(0,0,0);
	this -> colShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI(mass,motionState,colShape,inertia);
	this -> body = new btRigidBody(bodyCI);
}


Ball::~Ball(void)
{
}
