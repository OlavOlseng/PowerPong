#include "Ball.h"


Ball::Ball(float xPos, float zPos, float forceX, float forceY)
	:Entity(Entity::BALL_ID)
{
	this ->DEFAULT_RADIUS = 1.5;
	this ->DEFAULT_SPEED = 15.0f;
	this -> colShape = new btSphereShape(DEFAULT_RADIUS);
	this -> motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), *(new btVector3(xPos,0,zPos))));
	this -> mass = 5.0f;
	this -> inertia = btVector3(0,0,0);
	
	this -> colShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo bodyCI(mass,motionState,colShape,inertia);
	this-> body = new btRigidBody(bodyCI);

	//Ball specific property setup
	this->body ->applyCentralImpulse(btVector3(forceX,0,forceY));
	this->body ->setLinearFactor(btVector3(1.0, 0.0, 1.0));
	this->body->setAngularFactor(btVector3(4.0,4.0,4.0));
	this->body ->setDamping(0.0,0.0);
	this->body ->setRestitution(1.0);
	this->body ->setFriction(0.3);
	this->body->setRollingFriction(0.5);

	body->setUserPointer(this);
}

	

Ball::~Ball(void)
{
	
}