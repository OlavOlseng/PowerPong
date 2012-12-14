#include "Block.h"

Block::Block(){
	empty = true;
}

void Block::set(int width,int height,const glm::vec3 &color){
	this->color.x = color.x;
	this->color.y = color.y;
	this->color.z = color.z;
	empty = false;

}
Block::~Block(void)
{
}
