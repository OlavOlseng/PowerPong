#ifndef VOLUME_ENTITY
#define VOLUME_ENTITY
#include "Entity.h"
class VolumeEntity:public Entity
{
public:
	VolumeEntity(double x, double y,double z);
	~VolumeEntity(void);
	void useTriangleMesh(btTriangleMesh * collisionMesh);

	btTriangleMesh * collisionMesh;
private:
	btVector3 position;
};

#endif;