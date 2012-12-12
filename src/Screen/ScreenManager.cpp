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

Screen* ScreenManager::popScreen()
{
	Screen* scrn = scrnStack.back();
	scrnStack.pop_back();
	return scrn;
}

std::list<Screen*> ScreenManager::getToRender()
//iterates over screen stack and returns screens to be rendered
{

	std::list<Screen*> list;
	Screen* scrn;

	for (unsigned int i = 0; i < this -> scrnStack.size(); i++)
	{
		scrn = this -> scrnStack[i];
		if (scrn -> isRenderBlock())
		{
			list.clear();
		}
			list.push_back(scrn);
	};
	return list;
}

//std::list<Screen*> ScreenManager::getToUpdate()
