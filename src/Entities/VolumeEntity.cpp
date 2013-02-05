#include "VolumeEntity.h"


VolumeEntity::VolumeEntity(double x,double y,double z)
	:Entity(Entity::VOLUME_ID)
{
	this->position = btVector3(x,y,z);
}
void VolumeEntity::useTriangleMesh(btTriangleMesh * collisionMesh){

	this->collisionMesh = collisionMesh;
	this->colShape = new btBvhTriangleMeshShape((btStridingMeshInterface*)collisionMesh,false);

	this->motionState = new btDefaultMotionState((btTransform(btQuaternion(0,0,0,1),(position))));
	btRigidBody::btRigidBodyConstructionInfo constructInfo(0.0,motionState,colShape,btVector3(0.0,0.0,0.0));
	this->body = new btRigidBody(constructInfo);
	this->body->setRestitution(0.0);
	

}

VolumeEntity::~VolumeEntity(void)
{
}
