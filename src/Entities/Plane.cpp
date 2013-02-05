#include "Plane.h"


Plane::Plane(btVector3* normal, btVector3* origin)
{
	this -> colShape = new btStaticPlaneShape((*normal),0);
	this -> motionState = new btDefaultMotionState((btTransform(btQuaternion(0,0,0,1),(*origin))));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,motionState,colShape,btVector3(0,0,0));
	this -> body =  new btRigidBody(groundRigidBodyCI);
	this->body->setFriction(1.0);
}


Plane::~Plane(void)
{
}
