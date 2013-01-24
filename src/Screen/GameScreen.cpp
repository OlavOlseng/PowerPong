#include "GameScreen.h"

GameScreen::GameScreen(bool enableTest)
{
	this -> renderBlock = 1;
	this -> updateBlock = 1;

	this -> world = new World();
	if (enableTest)
	{
		test();
	}
}

void GameScreen::test()
{
	this -> world -> addEntity(new Ball(1,0,10,0));
}

GameScreen::~GameScreen(void)
{
	
}

void GameScreen::render()
{
	std::cout << "Rendering gamescreen" << std::endl;
	
}

void GameScreen::update(double dt)
{
	
	this -> world -> update(dt);
	std::cout << "Updating gamescreen" << std::endl;
}