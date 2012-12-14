#include "GameScreen.h"

GameScreen::GameScreen(void)
{
	this -> renderBlock = 1;
	this -> updateBlock = 1;
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
	std::cout << "Updating gamescreen" << std::endl;
}