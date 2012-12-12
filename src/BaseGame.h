#ifndef base_game_h
#define base_game_h

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <string>

class BaseGame
{
public:
	BaseGame();
	~BaseGame(void);





private:
	int width,height,lastTime;

protected:
	void init(std::string windowTitle,int width,int height);
	static BaseGame* BaseGame::instance;
	static void display();
	static void idle();
	static void onReshape(int width,int height);
	void swapBuffers();
	void postRedisplay();
	virtual void draw() = 0;
	virtual void update(double dt) = 0;
	virtual void reshape(int width, int height) = 0;

	
};



#endif