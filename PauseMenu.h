#pragma once

// Dependencies
#include "MenuSystem.h"

class CPauseMenu : public CMenuSystem
{
public:
	CPauseMenu(tle::I3DEngine* pMyEngine, MenuStates& state, int horiz, int vert, bool fullscreen);
	virtual ~CPauseMenu();

	// do cursor collision detection on the buttons
	virtual void ButtonPresses();
};

