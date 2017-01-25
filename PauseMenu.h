#pragma once

// Dependencies
#include "MenuSystem.h"

class CResourceManager;

class CPauseMenu : public CMenuSystem
{
public:
	CPauseMenu(CResourceManager* pResources, MenuStates& state, int horiz, int vert, bool fullscreen);
	virtual ~CPauseMenu();

	// do cursor collision detection on the buttons
	virtual void ButtonPresses(GameStates& state);
};

