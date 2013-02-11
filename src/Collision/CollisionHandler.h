#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <list>
#include <iostream>
#include "CollisionPair.h"

class CollisionHandler
{
public:
	CollisionHandler(void);
	~CollisionHandler(void);

	void addInvolvementFlags(int flags);
	int getInvolvementFlags();

	void addCollisionPair(CollisionPair* cp);
	void clear();
	void handleCollisions();

private:
	std::list<CollisionPair*> pairs;
	int involvementFilter;
	int typeFilter;
};

#endif