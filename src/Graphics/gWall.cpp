#include "gWall.h"


gWall::gWall(int blockScale,int lenght,glm::vec3 pos):vertexBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,4,GL_FLOAT),colorBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,4,GL_FLOAT)
{


	this->pos = pos;
	this->blockScale = blockScale;

	this->width = lenght;
	
	blocks = new gBlock[width];
	
	//Physics init
	
}
int gWall::getWidth(){
	return this->width;
}
void gWall::setBlock(int x,int width,glm::vec3 color){

	for (int i = x;i<x+width;i++)
		blocks[i].set(width,color);
	
	

}

gBlock gWall::getBlock(int x){

	
	gBlock block = blocks[x];
	return block;

}
glm::vec3 * gWall::getPosition(){
	return &this->pos;

}
Buffer *gWall::getVertexBuffer(){
	
	return &this->vertexBuffer;
	
}
Buffer*gWall::getColorBuffer(){

	return &this->colorBuffer;

}
gWall::~gWall(void)
{

}
