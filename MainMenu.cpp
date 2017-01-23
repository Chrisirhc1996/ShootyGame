//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "MainMenu.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CMainMenu::CMainMenu(tle::I3DEngine* pMyEngine, MenuStates& state, int horiz, int vert, bool fullscreen) :
	CMenuSystem(pMyEngine, horiz, vert, fullscreen)
{
	SetMenuState(state);

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