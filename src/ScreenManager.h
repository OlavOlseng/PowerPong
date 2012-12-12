#pragma once

#ifndef SCR_MNGR
#define SCR_MNGR

#include <stack>
#include "Screen.h"

class ScreenManager
{
public:
	ScreenManager(void);
	~ScreenManager(void);

	std::stack<Screen> ScrStack;

};

#endif