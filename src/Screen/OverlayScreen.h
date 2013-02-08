#pragma once

#ifndef OVLY_SCRN_H
#define	OVLY_SCRN_H

#include "../src/Rendering/Screen/Screen.h"

class OverlayScreen: public Screen
{
public:
	OverlayScreen(void);
	~OverlayScreen(void);

	virtual void update(double dt) override;
	virtual void render() override;
};

#endif