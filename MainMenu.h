#pragma once

// Dependencies
#include "MenuSystem.h"

class CResourceManager;

class CMainMenu : public CMenuSystem
{
public:
	CMainMenu(CResourceManager* pResources, MenuStates& state, int horiz, int vert, bool fullscreen);
	virtual ~CMainMenu();

	// do cursor collision detection on the buttons
	virtual void ButtonPresses(GameStates& state);
};

