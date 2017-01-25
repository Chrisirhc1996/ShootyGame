#pragma once

// Dependencies
#include "MenuSystem.h"

class CResourceManager;

class COptionsMenu : public CMenuSystem
{
public:
	COptionsMenu(CResourceManager* pResources, MenuStates& state, int horiz, int vert, bool fullscreen);
	virtual ~COptionsMenu();

	// do cursor collision detection on the buttons
	virtual void ButtonPresses(GameStates& state);
};

