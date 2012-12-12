#include "MenuScreen.h"


MenuScreen::MenuScreen(void)
{
	this -> updateBlock = 1;
	this -> renderBlock = 1;
}


MenuScreen::~MenuScreen(void)
{
}

void MenuScreen::render()
{
	std::cout << "Rendering MenuScreen" << std::endl;
}

void MenuScreen::update()
{
	std::cout << "Updating MenuScreen" << std::endl;
}