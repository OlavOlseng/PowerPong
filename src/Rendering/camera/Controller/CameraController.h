#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
#include "Behavior\Behavior.h"
#include <vector>
#include "../FreeMovementCamera.h"
#include <memory>
class CameraController
{
public:
	CameraController(Camera * camera);
	~CameraController(void);
	void addBehaviour(Behavior * behaviour);
	virtual void update(double dt) = 0;
protected:
	std::vector<Behavior*> behaviours;
	Camera * camera;

};
#endif
