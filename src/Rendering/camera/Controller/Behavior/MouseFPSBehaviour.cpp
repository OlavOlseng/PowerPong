#include "MouseFPSBehaviour.h"


MouseFPSBehaviour::MouseFPSBehaviour(bool inverted)
{
	this->inverted = inverted;
	this->speedX = 1.0;
	this->speedY = 1.0;
}


void MouseFPSBehaviour::setSpeedX(double speedX){

	this->speedX = speedX;
}
void MouseFPSBehaviour::setSpeedY(double speedY){

	this->speedY = speedY;
}
void MouseFPSBehaviour::setSpeed(double speedX,double speedY){
	this->speedX = speedX;
	this->speedY = speedY;

}

void MouseFPSBehaviour::setInverted(bool inverted){

	this->inverted = inverted;
}
void MouseFPSBehaviour::update(double dt){

	input.update();

	for each (Camera *  camera in this->getCameras())
	{
		if(inverted){
		camera->rotateRight(-input.getMouseChangeX()*dt);
		camera->rotateDown(-input.getMouseChangeY()*dt);	

		}else{
			camera->rotateRight(input.getMouseChangeX()*dt);
			camera->rotateDown(input.getMouseChangeY()*dt);	

		}
	}

}
MouseFPSBehaviour::~MouseFPSBehaviour(void)
{
}
