#pragma once

#ifndef G_SCRN_H
#define G_SCRN_H

#include "Screen.h"
#include "../World/World.h"
#include "../Entities/Ball.h"

class GameScreen: public Screen
{
public:
	GameScreen(bool enableTest);
	~GameScreen(void);
	
	World* world;

	virtual void update(double dt) override;
	virtual void render() override;

private:
	
	//temp
	void test();

};

#endif