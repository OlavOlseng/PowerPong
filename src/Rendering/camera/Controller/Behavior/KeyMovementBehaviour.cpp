#include "KeyMovementBehaviour.h"


KeyMovementBehaviour::KeyMovementBehaviour(KeyMap<Key,Direction> keyMap)
{
	this->keyMap = keyMap;
	speed = 1.0;
	
	for  (std::pair<char,std::pair<Key,Direction>> keypair : keyMap)
	{
		keys.push_back(std::make_pair(keypair.first,keypair.second.second));
	}
}

void KeyMovementBehaviour::setSpeed(double speed){

	this->speed = speed;

}
void KeyMovementBehaviour::update(double dt){

	input.update();

	for each (Camera *  camera in this->getCameras())
	{
		
		for (std::pair<char,Direction> keyPair :keys){
			
			if(input.keyPressed(keyPair.first)){
				camera->move(keyPair.second*(float)(dt*speed));
			}
			
		}

	}


}
KeyMovementBehaviour::~KeyMovementBehaviour(void)
{
}
