#pragma once

// Dependencies
#include "MenuSystem.h"

class CMainMenu : public CMenuSystem
{
public:
	CMainMenu(tle::I3DEngine* pMyEngine, MenuStates& state, int horiz, int vert, bool fullscreen);
	virtual ~CMainMenu();

	// do cursor collision detection on the buttons
	virtual void ButtonPresses(GameStates& state);
};
