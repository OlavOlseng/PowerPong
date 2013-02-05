#ifndef INPUT_HANDELR
#define INPUT_HANDLER

#include <GL\glfw.h>
class InputHandler

{
public:
	InputHandler(void);
	~InputHandler(void);

	bool keyPressed(char key);

	int getMouseX();
	int getMouseY();
	int getMouseChangeX();
	int getMouseChangeY();
	bool leftMouseButtonDown();
	bool leftMouseButtonClicked();
	bool rightMouseButtonDown();
	bool rightMouseButtonClicked();
	void update();
private:
	int mouseX;
	int mouseY;

	int mouseChangeX;
	int mouseChangeY;
	bool leftMouseDown;
	bool rightMouseDown;
	bool leftMouseClicked;
	bool rightMouseClicked;
};

#endif