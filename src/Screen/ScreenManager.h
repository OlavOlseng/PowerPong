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
	Screen* popScreen();
	std::list<Screen*> getToRender();
	std::list<Screen*> getToUpdate();
	

private:
	std::deque<Screen*> scrnStack;

};



#endif