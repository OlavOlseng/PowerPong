#include "ScreenManager.h"


ScreenManager::ScreenManager(void)
{
}


ScreenManager::~ScreenManager(void)
{
}

void ScreenManager::pushScreen(Screen* scrn)
{
	scrnStack.push_back(scrn);	
}

void ScreenManager::popScreen()
{
	scrnStack.pop_back();
}

std::list<Screen*> ScreenManager::getToRender()
//iterates over screen stack and returns screens to be rendered
{

	std::list<Screen*> list;
	Screen* scrn;

	for (unsigned int i = this -> scrnStack.size(); i >= this -> scrnStack.size(); i--)
	{
		scrn = this -> scrnStack[i];
		list.push_back(scrn);
		if (scrn -> isRenderBlock()) { break; }
	};
	return list;
}

//std::list<Screen*> ScreenManager::getToUpdate()
