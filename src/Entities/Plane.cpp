#include "Plane.h"


Plane::Plane(btVector3* normal, btVector3* origin)
	: Entity(Entity::PLANE_ID)
{
	this -> colShape = new btStaticPlaneShape((*normal),0);
	this -> motionState = new btDefaultMotionState((btTransform(btQuaternion(0,0,0,1),(*origin))));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,motionState,colShape,btVector3(0,0,0));
	this -> body =  new btRigidBody(groundRigidBodyCI);
	body->setUserPointer(this);
}


Plane::~Plane(void)
{
}
