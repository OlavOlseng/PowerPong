#include "Wall.h"


Wall::Wall(int blockScale,int width,int height,glm::vec3 pos):vertexBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC),colorBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC)
{


	this->pos = pos;
	this->blockScale = blockScale;
	this->height = height;
	this->width = width;
	blocks = new Block[width*height];
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
