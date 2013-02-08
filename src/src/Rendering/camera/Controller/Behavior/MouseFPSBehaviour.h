#ifndef MOUSE_FPS_BEHAVIOUR
#define MOUSE_FPS_BEHAVIOUR
#include "Behavior.h"

#ifndef INPUT_INPUT_HANDLER_H
#define INPUT_INPUT_HANDLER_H
#include "../../../../Input/InputHandler.h"
#endif

class MouseFPSBehaviour:public Behavior
{
public:
	MouseFPSBehaviour(bool inverted = false);
	~MouseFPSBehaviour(void);

	void update(double dt);
	void setSpeedX(double speedX);
	void setSpeedY(double speedY);
	void setSpeed(double speedX,double speedY);
	void setInverted(bool inverted);
private:
	bool inverted;
	double speedX;
	double speedY;
	InputHandler input;
	
};

#endif