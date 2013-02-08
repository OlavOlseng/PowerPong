#include "UnconstrainedCameraController.h"


UnconstrainedCameraController::UnconstrainedCameraController(Camera * camera):CameraController(camera)
{
}

void UnconstrainedCameraController::update(double dt){

	std::vector<Behavior*>::iterator iterator;

	for(iterator = behaviours.begin();iterator != behaviours.end(); iterator++){

		Behavior * behaviour= *iterator;
		behaviour->update(dt);

	}


}

UnconstrainedCameraController::~UnconstrainedCameraController(void)
{
}
