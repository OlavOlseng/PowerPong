#ifndef SURFACE_EXTRACTOR_H
#define SURFACE_EXTRACTOR_H

#include "VolumeSurface.h"
#include "../Volume/Volume.h"

class SurfaceExtractor
{
public:
	virtual VolumeSurface * extractSurface(unsigned int xStart,unsigned int yStart,unsigned int zStart,unsigned int width,unsigned int height,unsigned int depth) = 0;

private:

};


#endif