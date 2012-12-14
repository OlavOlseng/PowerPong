#pragma once

#ifndef G_SCRN_H
#define G_SCRN_H

#include "Screen.h"

class GameScreen: public Screen
{
public:
	GameScreen(void);
	~GameScreen(void);

	virtual void update(double dt) override;
	virtual void render() override;
};

#endif