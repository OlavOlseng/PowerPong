#ifndef CAMERA_BEHAVIOUR_H
#define CAMERA_BEHAVIOUR_H
#include "../../FreeMovementCamera.h"
#include <vector>
typedef FreeMovementCamera Camera;
class Behavior
{
public:
	Behavior(void);
	~Behavior(void);
	virtual void addCamera(Camera * camera);
	virtual void update(double dt) = 0;
	std::vector<Camera * > getCameras();
private:
	std::vector<Camera *> cameras;
};

#endif