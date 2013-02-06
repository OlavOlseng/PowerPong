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

int CollisionPair::getCollisionType()
{
	return entA->getClassID() + entB->getClassID();
}

bool CollisionPair::involves(int cID)
{
	if(entA->getClassID() == cID || entB->getClassID() == cID)
		return true;
}