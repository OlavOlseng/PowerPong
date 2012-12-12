#pragma once

#ifndef OVLY_SCRN_H
#define	OVLY_SCRN_H

#include "Screen.h"

class OverlayScreen: public Screen
{
public:
	OverlayScreen(void);
	~OverlayScreen(void);

	virtual void update() override;
	virtual void render() override;
};

#endif