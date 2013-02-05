#ifndef WORLD_H
#define WORLD_H

#pragma once

#include "..\bullet\btBulletDynamicsCommon.h"
#include "..\Entities\Entity.h"
#include "..\Entities\Ball.h"
#include "..\Entities\StaticWall.h"
#include "..\Entities\Block.h"
#include "..\Entities\Plane.h"
#include <iostream>
#include <list>
#include "BulletDebugDraw.h"
#include "../Collision/CollisionHandler.h"
//Will later be refactored to an abstract base class, for now it 
//is equivalent of the 2-player map.

class World
{
public:
	//==============
	//TEMP
	//==============
	
	
	World(void);
	~World(void);

	void init();
	void update(double dt);
	void render();

	void handleCollisions();
	static bool cProcCB(btManifoldPoint& cp, void* body0, void* body1);

	//Adding stuff to the world
	void addEntity(Entity*);
	void removeEntity(Entity*);

	std::list<Entity*> entities;
	void setDebugDraw(BulletDebugDraw* debugDraw);
	void debugDrawWorld();
	
	//Simulation wold params
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* simWorld;

private:
	BulletDebugDraw* debugDraw;
	void test();
	CollisionHandler* colHand;

};

#endif