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
	this -> addEntity(new Plane(new btVector3(0,1,0),new btVector3(0, 0.0,0)));

	//Setup collision handler
	this->colHand = new CollisionHandler();
	//Add collision callback
	gContactProcessedCallback = cProcCB;

	//test();
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
	this -> simWorld -> addRigidBody(ent->getBody());
	ent->setCollisionHandler(this->colHand);
}

std::list<Entity*>  World::getEntities(){
	return this->entities;

}

void World::removeEntity(Entity* ent)
{
	this-> entities.remove(ent);
	this->simWorld->removeRigidBody(ent->getBody());
}

void World::update(double dt)
{
	colHand->clear();
	this -> simWorld -> stepSimulation(dt);
	std::list<Entity*>::iterator it;	
	for (it = entities.begin(); it != entities.end(); it++)
	{
		if ((*it)->getClassID() == 1)
		{
			btVector3 speed = (*it)->getBody()->getLinearVelocity().normalized();
			speed.setX(speed.getX()*25);
			speed.setZ(speed.getZ()*25);
			(*it)->getBody()->setLinearVelocity(speed);
		}
	}
	colHand->handleCollisions();
}

/* DEPRACATED!
void World::handleCollisions()
{
	int numManifolds = simWorld->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  simWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());
		
		Entity* entA = ((Entity*)obA->getUserPointer());
		Entity* entB = ((Entity*)obB->getUserPointer());

		
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f && pt.m_lifeTime <= 1)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
				//std::cout << entA->ID << " " << entB->ID << std::endl << std::endl << cog << std::endl;
				cog++;
				break;
				
			}
		}
		
	}
}
*/

bool World::cProcCB(btManifoldPoint& cp, void* body0, void* body1)
{
	
	if(cp.m_lifeTime <= 1)
	{
		Entity* entA = (Entity*)(((btRigidBody*)body0)->getUserPointer());
		Entity* entB = (Entity*)(((btRigidBody*)body1)->getUserPointer());
		entA->getCollisionHandler()->addCollisionPair(new CollisionPair(cp,entA,entB));
	}

	return false;
}

void World::test()
{
	
	addEntity(new Ball(-4,4,31.0,78.0));
	addEntity(new Ball(4,4,31.0,-78.0));
	addEntity(new Ball(2,8,31.0,-78.0));
	addEntity(new Ball(1,1,-31.0,78.0));
	//addEntity(new Block(1,5,1,0,0,0));
	
	for(int x = 0; x < 5; x++){
		for(int y = 0; y < 5; y++)
			addEntity(new Block(x*4, y*4, x*y*4));
	}
	addEntity(new StaticWall(40,true,0,22));
	addEntity(new StaticWall(40,true,0,-22));
	addEntity(new StaticWall(40,false,22,0));
	addEntity(new StaticWall(40,false,-22,0));
}
