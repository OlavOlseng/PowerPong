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
	setToRender();
	setToUpdate();
}

void ScreenManager::popScreen()
{
	scrnStack.pop_back();
	setToRender();
	setToUpdate();
}

void ScreenManager::setToRender()
//iterates over screen stack and returns screens to be rendered
{
	toRender.clear();
	std::deque<Screen*>::reverse_iterator it;

	for (it = this -> scrnStack.rbegin(); it != this -> scrnStack.rend(); it++)
	{
		toRender.push_back(*it);
		if ((*it)->isRenderBlock()) { break; }
	};
}

void ScreenManager::setToUpdate()
//iterates over screen stack and returns screens to be updated
{
	toUpdate.clear();
	std::deque<Screen*>::reverse_iterator it;

	for (it = this -> scrnStack.rbegin(); it != this -> scrnStack.rend(); it++)
	{
		toUpdate.push_back(*it);
		if ((*it)->isUpdateBlock()) { break; }
	};
}

void ScreenManager::render()
{
	std::list<Screen*>::reverse_iterator it;
	for (it = toRender.rbegin(); it != toRender.rend(); it++)
	{
		(*it) -> render();
	}
}
