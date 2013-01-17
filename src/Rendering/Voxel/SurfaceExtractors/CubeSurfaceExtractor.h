#ifndef CUBE_SURFACE_EXTRACTOR_H
#define CUBE_SURFACE_EXTRACTOR_H

#include "../Volume/Volume.h"
#include "VolumeSurface.h"
class CubeSurfaceExtractor
{
public:
	CubeSurfaceExtractor(Volume * volume);
	~CubeSurfaceExtractor(void);

	VolumeSurface * extractSurface(unsigned int xStart,unsigned int yStart,unsigned int zStart,unsigned int width,unsigned int height,unsigned int depth);
	


private:
	Volume * volume;
};

#endif