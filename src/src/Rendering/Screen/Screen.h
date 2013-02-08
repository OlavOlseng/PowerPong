//Superclass for all screens, contains virtual methods that must be overwritten
//by all no virtual children

#pragma once

#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>

class Screen
{


public:
	Screen(void);
	~Screen(void);

	virtual void update(double dt) = 0;
	virtual void render() = 0;

	void setRenderBlock(bool b);
	void setUpdateBlock(bool b);

	bool isUpdateBlock();
	bool isRenderBlock();

	virtual void reshape(int width, int height) = 0;

protected:
	bool renderBlock;
	bool updateBlock;

};

#endif