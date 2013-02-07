#include "CameraController.h"


CameraController::CameraController(Camera * camera)
{
	this->camera = camera;

}

void CameraController::addBehaviour(Behavior *behaviour){

	behaviour->addCamera(camera);
	this->behaviours.push_back(behaviour);
}

CameraController::~CameraController(void)
{
}
