#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "..\bullet\btBulletDynamicsCommon.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void init() = 0;

protected:
	btCollisionShape* colShape;
	btMotionState* motionShape;

};

#endif