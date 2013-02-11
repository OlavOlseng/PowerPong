#pragma once

#ifndef MENU_SCRN_H
#define MENU_SCRN_H

#include <SGL/Rendering/Screen/Screen.h>

class MenuScreen: public Screen
{
public:
	MenuScreen(void);
	~MenuScreen(void);

	virtual void update(double dt) override;
	virtual void render() override;

};

#endif