#include "InputHandler.h"


InputHandler::InputHandler(void)
{
	mouseChangeX = 0;
	mouseChangeY = 0;
	leftMouseDown = false;
	leftMouseClicked = false;
	rightMouseDown = false;
	rightMouseClicked = false;
	glfwSetMousePos(0,0);
	glfwDisable(GLFW_MOUSE_CURSOR);
	update();
	
}


bool InputHandler::keyPressed(char key){

	
	return glfwGetKey(key) == GLFW_PRESS;
}


int InputHandler::getMouseX(){

	return mouseX;

}

int InputHandler::getMouseY(){

	return mouseY;
}


int InputHandler::getMouseChangeX(){

	return mouseChangeX;
}

int InputHandler::getMouseChangeY(){

	return mouseChangeY;

}
bool InputHandler::leftMouseButtonDown(){

	
	return leftMouseDown;
}

bool InputHandler::leftMouseButtonClicked(){

	return leftMouseClicked;

}

bool InputHandler::rightMouseButtonDown(){

	return rightMouseDown;
}

bool InputHandler::rightMouseButtonClicked(){

	return rightMouseClicked;
}

void InputHandler::update(){
	glfwPollEvents();
	int tempX, tempY;
	bool leftWasDown,rightWasDown;
	glfwGetMousePos(&tempX,&tempY);
	
	mouseChangeX = tempX - mouseX;
	mouseChangeY = tempY - mouseY;
	mouseX = tempX;
	mouseY = tempY;

	leftWasDown = leftMouseDown;
	rightWasDown = rightMouseDown;

	leftMouseDown = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
	rightMouseDown = glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT);

	if(leftWasDown)
		leftMouseClicked = false;
	else if(leftMouseDown)
		leftMouseClicked = true;

	if(rightWasDown)
		rightMouseClicked = false;
	else if(rightMouseDown)
		rightMouseClicked = true;

	

	

	

	


}
InputHandler::~InputHandler(void)
{
}
