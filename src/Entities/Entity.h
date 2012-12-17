#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "..\bullet\btBulletDynamicsCommon.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	btScalar mass;
	btVector3 inertia;
	btTransform trans;
	btScalar modelMatrix;
	
	float* getModelMatrix();
	btCollisionShape* colShape;
	btMotionState* motionState;
	btRigidBody* body;
	
	//TODO
	void setPosition();
	void setOrientation();


};

#endif