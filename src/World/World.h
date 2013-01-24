#ifndef WORLD_H
#define WORLD_H

#pragma once

#include "..\bullet\btBulletDynamicsCommon.h"
#include "..\Entities\Entity.h"
#include "..\Entities\Plane.h"
#include <iostream>
#include <list>

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
	
	//Adding stuff to the world
	void addEntity(Entity*);
	void removeEntity(Entity*);

	std::list<Entity*> entities;
	
	//Simulation wold params
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* simWorld;

};

#endif