#ifndef FREE_MOVEMENT_CAMERA_H
#define FREE_MOVEMENT_CAMERA_H
#include "camera.h"

#include <glm\gtx\quaternion.hpp>



namespace Direction{
	const glm::vec3 Forward = glm::vec3(0.0,0.0,-1.0);
	const glm::vec3 Backwards = glm::vec3(0.0,0.0,1.0);
	const glm::vec3 Up = glm::vec3(0.0,1.0,0.0);
	const glm::vec3 Down = glm::vec3(0.0,-1.0,0.0);
	const glm::vec3 Left = glm::vec3(-1.0,0.0,0.0);
	const glm::vec3 Right = glm::vec3(1.0,0.0,0.0);


}

class FreeMovementCamera
{
public:
	
	
	//orientation as Quaternion
	FreeMovementCamera(float x,float y,float z,int width,int height,glm::quat orientation = glm::quat(),float zNear = 0.1,float zFar = 300);
	~FreeMovementCamera(void);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	
	void setProjection(int width,int height);
	glm::vec3 getViewDirection();
	glm::vec3 getPosition();
	void rotate(double x,double y,double z);
	void move(double x,double y,double z);
	void lookAt(double x,double y,double z);
	void rotateUp(double amount);
	void rotateDown(double amount);
	void rotateLeft(double amount);
	void rotateRight(double amount);

	void rotateAroundAxis(double amount , double x,double y,double z);

	void setPosition(double x,double y,double z);
	void move(glm::vec3 direction);

private:
	
	glm::quat orientation;
	glm::vec3 unitVector;
	glm::vec3 position;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	float zNear,zFar;
};

#endif