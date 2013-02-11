#include "CollisionPair.h"
#include "../Entities/Entity.h"

CollisionPair::CollisionPair(btManifoldPoint& cp, Entity* entA, Entity* entB)
{
	this->entA = entA;
	this->entB = entB;
	this->cp = cp;
}

CollisionPair::~CollisionPair(void)
{
}

Entity* CollisionPair::getEntA()
{
	return entA;
}

Entity* CollisionPair::getEntB()
{
	return entB;
}

btManifoldPoint CollisionPair::getManifoldPoint()
{
	return this->cp;
}

int CollisionPair::isCollisionType(int collisionType)
{
	return ((entA->getClassID() + entB->getClassID()) == collisionType);
}

bool CollisionPair::involves(int cID)
{
	return ((entA->getClassID() | entB->getClassID()) & cID);
}