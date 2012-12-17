#include "World.h"


World::World(void)
{
	this -> init();
}


World::~World(void)
{
    dynamicsWorld->removeRigidBody(groundBody);
    delete groundBody->getMotionState();
    delete groundBody;
 
    delete groundShape;
 
    delete dynamicsWorld;
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
    this -> dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));

	// Build the static ground and add it to the simulation
	this -> groundShape = new btStaticPlaneShape(btVector3(0,0,0),1);
	this -> groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    this -> groundBody = new btRigidBody(groundRigidBodyCI);
	this -> dynamicsWorld->addRigidBody(groundBody);

}