#ifndef UNCONSTRAINED_CAMERA_CONTROLLER_H
#define UNCSONTRAINED_CAMERA_CONTROLLER_H
#include "CameraController.h"
class UnconstrainedCameraController:public CameraController
{
public:
	UnconstrainedCameraController(Camera * camera);

	void update(double dt);
	~UnconstrainedCameraController(void);
};

#endif