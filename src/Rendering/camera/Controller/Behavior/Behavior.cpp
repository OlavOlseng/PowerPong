#include "Behavior.h"


Behavior::Behavior(void)
{
}

void Behavior::addCamera(Camera * camera){

	cameras.push_back(camera);



}

std::vector<Camera * >  Behavior::getCameras(){

	return this->cameras;

}
Behavior::~Behavior(void)
{
}
