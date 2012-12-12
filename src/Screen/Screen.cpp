#include "Screen.h"


Screen::Screen(void)
{
	this -> renderBlock = 0;
	this -> updateBlock = 1;
}


Screen::~Screen(void)
{
}

void Screen::setRenderBlock(bool b)
{
	this -> updateBlock = b;
}

void Screen::setUpdateBlock(bool b)
{
	this -> renderBlock = b;
}

bool Screen::isUpdateBlock()
{
	return this -> updateBlock;
}

bool Screen::isRenderBlock()
{
	return this -> renderBlock;
}
