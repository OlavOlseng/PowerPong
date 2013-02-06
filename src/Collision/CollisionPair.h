#pragma once
#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include "btBulletDynamicsCommon.h"
class Entity;

class CollisionPair
{
public:
	CollisionPair(btManifoldPoint& cp, Entity* entA, Entity* entB);
	~CollisionPair(void);

	Entity* getEntA();
	Entity* getEntB();
	btManifoldPoint getManifoldPoint();
	int getCollisionType();
	bool involves(int cID);

private:
	Entity* entA;
	Entity* entB;
	btManifoldPoint cp;

};

#endif