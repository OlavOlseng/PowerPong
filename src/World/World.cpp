#include "World.h"


World::World(void)
{
	this -> init();
	
	//TEMP

}


World::~World(void)
{
 
    delete simWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;
}

void World::init()
{
	
	// Build the broadphase
	this -> broadphase = new btDbvtBroadphase();
 
    // Set up the collision configuration and dispatcher
    this -> collisionConfiguration = new btDefaultCollisionConfiguration();
    this -> dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    // The actual physics solver
    this -> solver = new btSequentialImpulseConstraintSolver;
 
    // The simulation world
    this -> simWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	simWorld->setGravity(btVector3(0,-10,0));

	// Build the static ground and add it to the simulation
	this -> addEntity(new Plane(new btVector3(0,1,0),new btVector3(0,0,0)));

	
	
}

void World::setDebugDraw(BulletDebugDraw* debugDraw){
	this -> debugDraw = debugDraw;
	this -> simWorld->setDebugDrawer(debugDraw);

}

void World::debugDrawWorld(){

	 this -> simWorld->debugDrawWorld();
	this->debugDraw->render();

}
void World::addEntity(Entity* ent)
{
	this-> entities.push_back(ent);
	this -> simWorld -> addRigidBody(ent->body);
}

std::list<Entity*>  World::getEntities(){
	return this->entities;

}

void World::removeEntity(Entity* ent)
{
	this-> entities.remove(ent);
}

void World::update(double dt)
{
	this -> simWorld -> stepSimulation(dt);

	/*
	for(std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++){
	
	}
	*/
}
