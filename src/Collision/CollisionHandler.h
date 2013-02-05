#pragma once
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

	void addCollisionPair(CollisionPair* cp);
	void clear();
	void handleCollisions();

private:
	std::list<CollisionPair*> pairs;
};

#endif