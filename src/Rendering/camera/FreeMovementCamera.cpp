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

void FreeMovementCamera::setPosition(double x,double y,double z){
	this->position = glm::vec3(x,y,z);

}
void FreeMovementCamera::lookAt(double x,double y,double z){
	


	throw "not implemented";

}

void FreeMovementCamera::rotate(double x,double y,double z){

	glm::quat rotation = glm::quat(glm::vec3(x,y,z));
	//apply the rotation
	this->orientation = glm::normalize(rotation*orientation);
	//get the new viewDirection
	unitVector = glm::normalize(unitVector * rotation);

}
#include <iostream>
void FreeMovementCamera::rotateUp(double amount){
	
	rotateAroundAxis(-amount,unitVector.z,0,-unitVector.x);
	
}

void FreeMovementCamera::rotateDown(double amount){

	rotateAroundAxis(amount,unitVector.z,0,-unitVector.x);

}



void FreeMovementCamera::rotateLeft(double amount){
	rotateAroundAxis(amount,0.0,1.0,0.0);
	

}
void FreeMovementCamera::rotateRight(double amount){
	rotateAroundAxis(-amount,0.0,1.0,0.0);

}

void FreeMovementCamera::rotateAroundAxis(double amount , double x,double y,double z){

	double degrees = glm::degrees(amount);
	glm::quat rotation = glm::angleAxis((float)degrees,glm::normalize(glm::vec3(x,y,z)));
		std::cout << "unitVector: " <<"x:" << unitVector.x << "y:" << unitVector.y << "z:" << unitVector.z << std::endl;
		std::cout << "axis : " << ":x" << x << "y:" << y << "z:" << z << std::endl;
		std::cout << "dot : " << glm::dot(unitVector,glm::normalize(glm::vec3(x,y,z))) << std::endl;
		std::cout << "length :" << glm::length(unitVector) << std::endl;
		
	orientation = glm::normalize(rotation * orientation );
	unitVector = glm::normalize(rotation * unitVector);

	



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
