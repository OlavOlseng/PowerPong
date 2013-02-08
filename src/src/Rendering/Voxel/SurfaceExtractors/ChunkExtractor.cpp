#include "ChunkExtractor.h"


ChunkExtractor::ChunkExtractor(SurfaceExtractor * extractor,int chunkWidth,int chunkHeight,int chunkDepth)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkDepth = chunkDepth;



	this->extractor = extractor;
}


VolumeSurface * ChunkExtractor::extractSurface(int x,int y,int z){

	return  extractor->extractSurface(x*chunkWidth,y*chunkHeight,z*chunkDepth,chunkWidth,chunkHeight,chunkDepth);

}

ChunkExtractor::~ChunkExtractor(void)
{
}
