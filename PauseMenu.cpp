//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "PauseMenu.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPauseMenu::CPauseMenu(tle::I3DEngine* pMyEngine, MenuStates& state, int horiz, int vert, bool fullscreen) :
	CMenuSystem(pMyEngine, horiz, vert, fullscreen)
{
	SetMenuState(state);

	// create menu buttons
	// CreateButton(PLAY);
}


CPauseMenu::~CPauseMenu()
{
}

// do cursor collision detection on the buttons
void CPauseMenu::ButtonPresses()
{
	UpdateMousePos();

	SelectMenuOption();
}