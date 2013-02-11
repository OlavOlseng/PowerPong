#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <bullet\btBulletDynamicsCommon.h>
#include <glm\glm.hpp>
#include "../Collision/CollisionPair.h"
#include "../Collision/CollisionHandler.h"

typedef int ClassID;
typedef int EntityID;

static int uID = 0;



class Entity
{
	
public:

	static const int BALL_ID = 1;
	static const int PADDLE_ID = 2;
	static const int BLOCK_ID = 4;
	static const int STATIC_WALL_ID = 8;
	static const int PLANE_ID = 16;
	static const int VOLUME_ID = 256;

	float* modelMatrix;
	
	Entity(ClassID cID);
	~Entity(void);

	EntityID getEntityID();
	ClassID getClassID();
	float* getPosition();
	float* getModelMatrix();
	btRigidBody* getBody();
	void setCollisionHandler(CollisionHandler* h);
	CollisionHandler* getCollisionHandler();
	btQuaternion  getOrientation();
	void setUserPointer(void * ptr);
	void *  getUserPointer();

protected:
	
	ClassID cID;
	EntityID entID;
	
	btScalar mass;
	btVector3 inertia;
	btCollisionShape* colShape;
	btMotionState* motionState;
	btRigidBody* body;
	int health;


private:
	CollisionHandler* colHand;
};

#endif