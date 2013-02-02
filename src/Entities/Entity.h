#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "..\bullet\btBulletDynamicsCommon.h"
#include <glm\glm.hpp>



class Entity
{
public:
	Entity(void);
	~Entity(void);

	btScalar mass;
	btVector3 inertia;
	float* modelMatrix;
	
	float* getModelMatrix();
	btCollisionShape* colShape;
	btMotionState* motionState;
	btRigidBody* body;

	float * getPosition();

	void setUserPointer(void * ptr);
	void *  getUserPointer();
	

};

#endif