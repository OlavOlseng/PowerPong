#include "OctreeVolume.h"


OctreeVolume::OctreeVolume(unsigned int size,unsigned int dummyY ,unsigned int dummyZ)
{
	blocks = new Octree<BlockType>(size,0);
	this->size = size;
}



void OctreeVolume::set(int x,int y,int z,BlockType type){
	if(!blocks->at(x,y,z))
		numBlocks++;
	blocks->set(x,y,z,type);


}
BlockType OctreeVolume::get(int x,int y,int z){
	return blocks->at(x,y,z);
}

bool OctreeVolume::isInvisible(){

	return this->invisible;
}
bool OctreeVolume::isEmpty(){

	return numBlocks > 0;
}


unsigned int  OctreeVolume::getWidth(){

	return  this->size;
}
unsigned int  OctreeVolume::getHeight(){
	
	return this->size;
}
unsigned int  OctreeVolume::getDepth(){

	return this->size;
}

void OctreeVolume::setInvisible(bool invisible){
	
	this->invisible = invisible;
}
OctreeVolume::~OctreeVolume(void)
{
	delete blocks;
}
