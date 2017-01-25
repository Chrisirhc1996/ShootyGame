//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "MainMenu.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CMainMenu::CMainMenu(CResourceManager* pResources, MenuStates& state, int horiz, int vert, bool fullscreen) :
	CMenuSystem(pResources, state, horiz, vert, fullscreen)
{
	// create menu buttons
	CreateButton(PLAY);
	CreateButton(OPTIONS);
	CreateButton(QUIT);
}


CMainMenu::~CMainMenu()
{
}

// do cursor collision detection on the buttons
void CMainMenu::ButtonPresses(GameStates& state)
{
	UpdateMousePos();

	SelectMenuOption(state);
}