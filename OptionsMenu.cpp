//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "OptionsMenu.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

COptionsMenu::COptionsMenu(CResourceManager* pResources, MenuStates& state, int horiz, int vert, bool fullscreen) :
	CMenuSystem(pResources, state, horiz, vert, fullscreen)
{
	// create menu buttons

}


COptionsMenu::~COptionsMenu()
{
}

// do cursor collision detection on the buttons
void COptionsMenu::ButtonPresses(GameStates& state)
{
	UpdateMousePos();

	SelectMenuOption(state);
}