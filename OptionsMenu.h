#pragma once

// Dependencies
#include "MenuSystem.h"

class COptionsMenu : public CMenuSystem
{
public:
	COptionsMenu(tle::I3DEngine* pMyEngine, MenuStates& state, int horiz, int vert, bool fullscreen);
	virtual ~COptionsMenu();

	// do cursor collision detection on the buttons
	virtual void ButtonPresses(GameStates& state);
};

