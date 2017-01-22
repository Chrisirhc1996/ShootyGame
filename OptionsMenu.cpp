//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "OptionsMenu.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

COptionsMenu::COptionsMenu(tle::I3DEngine* pMyEngine, MenuStates& state, int horiz, int vert, bool fullscreen) :
	CMenuSystem(pMyEngine, horiz, vert, fullscreen)
{
	SetMenuState(state);

	// create menu buttons
	// CreateButton(PLAY);
}


COptionsMenu::~COptionsMenu()
{
}

// do cursor collision detection on the buttons
void COptionsMenu::ButtonPresses()
{
	UpdateMousePos();

	SelectMenuOption();
}