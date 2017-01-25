//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "PauseMenu.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPauseMenu::CPauseMenu(CResourceManager* pResources, MenuStates& state, int horiz, int vert, bool fullscreen) :
	CMenuSystem(pResources, state, horiz, vert, fullscreen)
{
	// create menu buttons
	CreateButton(UNPAUSE);
	CreateButton(PAUSE_OPTIONS);
	CreateButton(QUIT_TO_MENU);
}


CPauseMenu::~CPauseMenu()
{
}

// do cursor collision detection on the buttons
void CPauseMenu::ButtonPresses(GameStates& state)
{
	UpdateMousePos();

	SelectMenuOption(state);
}