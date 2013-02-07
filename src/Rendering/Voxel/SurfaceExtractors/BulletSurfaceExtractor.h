#ifndef BULLET_SURFACE_EXTRACTOR
#define BULLET_SURFACE_EXTRACTOR
#include "../../../bullet/btBulletDynamicsCommon.h"

#include "../Volume/Volume.h"
#include "SurfaceExtractor.h"
class BulletSurfaceExtractor
{
public:
	BulletSurfaceExtractor(Volume * volume);
	~BulletSurfaceExtractor(void);
	btTriangleMesh * extractBulletMesh(unsigned int xStart,unsigned int yStart,unsigned int zStart,unsigned int width,unsigned int height,unsigned int depth);
private:
	Volume * volume;
};

#endif