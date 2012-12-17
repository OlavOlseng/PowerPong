#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "..\bullet\btBulletDynamicsCommon.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	//virtual void init() =0;
	btScalar mass;
	btMotionState* getMotionState();
	btVector3 inertia;
	btTransform trans;
	float getY();

	btCollisionShape* colShape;
	btMotionState* motionState;
	btRigidBody* body;
};

#endif