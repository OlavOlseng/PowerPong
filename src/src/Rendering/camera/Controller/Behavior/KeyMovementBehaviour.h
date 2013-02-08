#ifndef KEY_MOVEMENT_BEHAVIOUR_H
#define KEY_MOVEMENT_BEHAVIOUR_H
#include "../../../../Input/KeyMap.h"
#include <glm\glm.hpp>
#include "Behavior.h"

#ifndef INPUT_INPUT_HANDLER_H
#define INPUT_INPUT_HANDLER_H
#include "../../../../Input/InputHandler.h"
#endif
typedef glm::vec3 Direction;

class KeyMovementBehaviour:public Behavior
{
public:
	enum Key{LEFT,RIGHT,FORWARD,BACKWARDS,UP,DOWN};
	KeyMovementBehaviour(KeyMap<Key,Direction> keyMap);
	~KeyMovementBehaviour(void);
	void update(double dt);
	void setSpeed(double speed);

private:
	KeyMap<Key,Direction> keyMap;
	std::vector<std::pair<char,Direction>> keys;
	InputHandler input;
	double speed;
};

#endif