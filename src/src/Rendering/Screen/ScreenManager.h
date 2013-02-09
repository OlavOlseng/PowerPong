#pragma once

#ifndef SCRN_MNGR_H
#define SCRN_MNGR_H

#include <deque>
#include <vector>
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
	void update(double dt);

private:
	std::deque<Screen*> scrnStack;
	std::vector<Screen*> toUpdate;
	std::vector<Screen*> toRender;
};



#endif