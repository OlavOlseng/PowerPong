#ifndef base_game_h
#define base_game_h
#include <GL\glew.h>

#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glfw.h>
#include <glm\glm.hpp>

#include <string>

class BaseGame
{
public:
	BaseGame();
	~BaseGame(void);





private:
	int width,height;
	double lastTime;


protected:
	void enterMainLoop();
	bool setupDone;
	void init(std::string windowTitle,int width,int height);
	virtual void draw() = 0;
	virtual void update(double dt) = 0;
	virtual void reshape(int width, int height) = 0;
	virtual void setup() = 0;
	void swapBuffers();
	

	
};



#endif