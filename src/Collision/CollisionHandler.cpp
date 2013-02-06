#include "CollisionHandler.h"


CollisionHandler::CollisionHandler(void)
{
}

CollisionHandler::~CollisionHandler(void)
{
}

void CollisionHandler::addCollisionPair(CollisionPair* cp)
{
	pairs.push_back(cp);
}

void CollisionHandler::clear()
{
	pairs.clear();
}

void CollisionHandler::handleCollisions()
{
	std::list<CollisionPair*>::iterator it;
	for(it = pairs.begin(); it != pairs.end(); it++)
	{
		if ((*it)->getCollisionType() == 2)
		{
	//		std::cout << "BALLS COLLIDE!" <<  std::endl;
		}
		
		else if ((*it)->getCollisionType() == 9)
		{
	//		std::cout << "BALLS TO THE WALLS!" << std::endl;
			
		}
		else if ((*it)->getCollisionType() == 5)
		{
	//		std::cout << "BALL BLOCK!" << std::endl;
			
		}
		else if ((*it)->getCollisionType() == 8)
		{
	//		std::cout << "BLOCKA BLOCK!" << std::endl;
			
		}
	}
}

