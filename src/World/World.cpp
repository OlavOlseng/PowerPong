#include "World.h"


World::World(void)
{
	this -> init();
	
	//TEMP

}


World::~World(void)
{
    simWorld->removeRigidBody(groundBody);
    delete groundBody->getMotionState();
    delete groundBody;
 
    delete groundShape;
 
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
	this -> groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
	this -> groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    this -> groundBody = new btRigidBody(groundRigidBodyCI);
	this -> simWorld->addRigidBody(groundBody);

}

void World::addEntity(Entity* ent)
{
	this-> entities.push_back(ent);
	this -> simWorld -> addRigidBody(ent->body);
}

void World::removeEntity(Entity* ent)
{
	this-> entities.remove(ent);
}

void World::update(double dt)
{
	this -> simWorld -> stepSimulation(dt);
	for(std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++){
	
	}
}
