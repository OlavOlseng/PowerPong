#pragma once

#ifndef SCRN_MNGR_H
#define SCRN_MNGR_H

#include <deque>
#include <list>
#include "Screen.h"

class ScreenManager
{

public:
	ScreenManager(void);
	~ScreenManager(void);
	void pushScreen(Screen* scrn);
	void popScreen();
	void setToRender();
	void setToUpdate();	
	void render();

private:
	std::deque<Screen*> scrnStack;
	std::list<Screen*> toUpdate;
	std::list<Screen*> toRender;
};



#endif