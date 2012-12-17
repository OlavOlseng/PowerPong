#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
	delete colShape;
	delete motionState;
	delete body;
}

btScalar* Entity::getModelMatrix()
{
	body-> getMotionState()->getWorldTransform(trans);
	trans.getOpenGLMatrix(&modelMatrix);
	return &modelMatrix;
}
