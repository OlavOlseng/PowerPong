#include "gBlock.h"

gBlock::gBlock(){
	empty = false;
	this->color = glm::vec3(0.0,0.0,0.0);
	this->type = BlockType::NONE;
}

void gBlock::set(int width, glm::vec3 color){

	this->color.x = color.x;
	this->color.y = color.y;
	this->color.z = color.z;
	this->width = width;

	empty = false;

}
void gBlock::set(int width,BlockType type){

	this->type = type;
	this->width = width;
	empty = false;



}
gBlock::~gBlock(void)
{
}
