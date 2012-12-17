#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "..\bullet\btBulletDynamicsCommon.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	virtual void init() =0;

	btMotionState* getMotionState();

protected:
	btCollisionShape* colShape;
	btMotionState* motionState;
	btRigidBody* body;
};

#endif