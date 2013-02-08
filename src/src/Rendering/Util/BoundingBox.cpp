#include "BoundingBox.h"


BoundingBox::BoundingBox(void)
{
}


void BoundingBox::setBounds(double xMin,double xMax,double yMin,double yMax,double zMin,double zMax){

	this->width = xMax-xMin;
	this->height = yMax - yMin;
	this->depth = zMax-zMin;

	this->center = glm::vec3((xMin + xMax)/2.0,(yMin + yMax)/2.0,(zMin + zMax)/2.0);

}


float BoundingBox::getWidth(){
	return this->width;
}

float BoundingBox::getHeight(){
	return this->height;
}

float BoundingBox::getDepth(){
	return this->depth;
}
glm::vec3 BoundingBox::getSize(){

	return glm::vec3(width,height,depth);
}

glm::vec3 BoundingBox::getCenter(){
	return this->center;
}

BoundingBox::~BoundingBox(void)
{
}
