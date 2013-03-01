#include "CollisionHandler.h"

CollisionHandler::CollisionHandler(void)
{
	involvementFilter = 0;
}

CollisionHandler::~CollisionHandler(void)
{
}

void CollisionHandler::addInvolvementFlags(int flags)
{
	this->involvementFilter = flags;
}

int CollisionHandler::getInvolvementFlags()
{
	return involvementFilter;
}

void CollisionHandler::addCollisionPair(CollisionPair* cp)
{
	if (cp->involves(involvementFilter)){
		pairs.push_back(cp);
	}
}


void CollisionHandler::clear()
{
	pairs.clear();
}

void CollisionHandler::handleCollisions()
{
}