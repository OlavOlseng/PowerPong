#include "FreeMovementCamera.h"



FreeMovementCamera::FreeMovementCamera(float x,float y,float z,int width,int height,glm::quat orientation)
{
	this->unitVector = glm::vec3(0.0,0.0,-1.0);
	
	
	this->orientation = orientation;
	this->position = glm::vec3(x,y,z);
	setProjection(width,height);
	

	
}


glm::mat4 FreeMovementCamera::getViewMatrix(){
	glm::mat4 trans = glm::translate(glm::mat4(1.0),-position);
	glm::mat4 rot = glm::mat4_cast(glm::inverse(orientation));
	
	return rot*trans;

}


void FreeMovementCamera::move(double x,double y,double z){
	this->position = this->position + glm::vec3(x,y,z);

}
void FreeMovementCamera::lookAt(double x,double y,double z){
	this->unitVector = glm::normalize( glm::vec3(x,y,z) - this->position);
	
	glm::vec3 e = glm::vec3(glm::dot(unitVector , glm::vec3(0.0f,1.0f,0.0f)),
	glm::dot(unitVector,glm::vec3(0.0f,1.0f,0.0f)),
	glm::dot(unitVector , glm::vec3(0.0f,1.0f,0.0f)));
	
	this->orientation =glm::quat(glm::vec3(asin(e.x),0.0,.0));

}

void FreeMovementCamera::roate(double x,double y,double z){

	glm::quat rotation = glm::quat(glm::vec3(x,y,z));
	this->orientation = rotation*orientation;
	unitVector = unitVector*rotation;

}

glm::mat4 FreeMovementCamera::getProjectionMatrix(){

	return projectionMatrix;

}
void FreeMovementCamera::setProjection(int width,int height){
	projectionMatrix = glm::perspective(50.0,1.0*width/height,0.1,300.0);


}
glm::vec3 FreeMovementCamera::getViewDirection(){

	return unitVector;

}
glm::vec3 FreeMovementCamera::getPosition(){

	return this->position;
}

FreeMovementCamera::~FreeMovementCamera(void)
{
}
