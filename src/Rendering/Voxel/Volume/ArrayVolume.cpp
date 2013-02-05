#include "ArrayVolume.h"


ArrayVolume::ArrayVolume(int width,int height,int depth){

	this->width = width;
	this->height = height;
	this->depth = depth;
	numBlocks = 0;
	invisible = false;
	this->blocks = new BlockType[width*height*depth];
	

};
ArrayVolume::~ArrayVolume(void){


};

void ArrayVolume::set(int x,int y,int z,BlockType type){
	if(!get(x,y,z))
		numBlocks++;
	this->blocks[getIndex(x,y,z)] = type;

};
BlockType ArrayVolume::get(int x,int y,int z){
	return this->blocks[getIndex(x,y,z)];

};
bool ArrayVolume::isInvisible(){
	return invisible;

};
bool ArrayVolume::isEmpty(){
	return numBlocks == 0;

};
void ArrayVolume::setInvisible(bool invisible){
	this->invisible = invisible;
};

int ArrayVolume::getIndex(int x,int y,int z){
	return x + y*height*height+ z*depth;

}
unsigned int ArrayVolume::getWidth(){
	return this->width;
};
unsigned int ArrayVolume::getHeight(){

	return this->height;
};
unsigned int ArrayVolume::getDepth(){
	return this->depth;
};
