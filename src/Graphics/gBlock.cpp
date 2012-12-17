#include "gBlock.h"

gBlock::gBlock(){
	empty = true;
	this->color = glm::vec4(0.0,0.0,0.0,1.0);

}

void gBlock::set(int width, glm::vec3 color){

	this->color.x = color.x;
	this->color.y = color.y;
	this->color.z = color.z;
	this->width = width;

	empty = false;

}
gBlock::~gBlock(void)
{
}
