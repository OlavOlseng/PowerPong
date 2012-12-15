#include "Wall.h"


Wall::Wall(int blockScale,int lenght,glm::vec3 pos):vertexBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC),colorBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC)
{


	this->pos = pos;
	this->blockScale = blockScale;

	this->width = lenght;
	
	blocks = new Block[width];
	

	
}
int Wall::getWidth(){
	return this->width;
}
void Wall::setBlock(int x,int width,glm::vec3 color){

	for (int i = x;i<x+width;i++)
		blocks[i].set(width,color);
	
	

}

Block Wall::getBlock(int x){

	
	Block block = blocks[x];
	return block;

}
glm::vec3 * Wall::getPosition(){
	return &this->pos;

}
Buffer *Wall::getVertexBuffer(){
	
	return &this->vertexBuffer;
	
}
Buffer*Wall::getColorBuffer(){

	return &this->colorBuffer;

}
Wall::~Wall(void)
{

}
