#ifndef CHUNK_EXTRACTOR_H
#define CHUNK_EXTRACTOR_H
#include "SurfaceExtractor.h"
class ChunkExtractor
{
public:
	ChunkExtractor(SurfaceExtractor * extractor,int chunkWidth,int chunkHeight,int chunkDepth);

	VolumeSurface * extractSurface(int x,int y,int z);
	~ChunkExtractor(void);

private:
	SurfaceExtractor * extractor;
	int chunkWidth,chunkHeight,chunkDepth;

};

#endif