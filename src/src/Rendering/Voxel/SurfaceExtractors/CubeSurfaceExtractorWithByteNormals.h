#ifndef CUBE_SURFACE_EXTRACTOR_WITH_NORMALS_H
#define CUBE_SURFACE_EXTRACTOR_WITH_NORMALS_H
#include "SurfaceExtractor.h"
class CubeSurfaceExtractorWithByteNormals: public SurfaceExtractor
{
public:
	CubeSurfaceExtractorWithByteNormals(Volume * volume);
	~CubeSurfaceExtractorWithByteNormals(void);

	VolumeSurface * extractSurface(unsigned int xStart,unsigned int yStart,unsigned int zStart,unsigned int width,unsigned int height,unsigned int depth);
private:
	Volume * volume;
};

#endif