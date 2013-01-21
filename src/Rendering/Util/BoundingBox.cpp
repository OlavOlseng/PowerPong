#include "BoundingBox.h"


BoundingBox::BoundingBox(void)
{
}


void BoundingBox::setBounds(double xMin,double xMax,double yMin,double yMax,double zMin,double zMax){
	this->center = glm::vec3((xMin + xMax)/2.0,(yMin + yMax)/2.0,(zMin + zMax)/2.0);

}

glm::vec3 BoundingBox::getCenter(){
	return this->center;
}

BoundingBox::~BoundingBox(void)
{
}
