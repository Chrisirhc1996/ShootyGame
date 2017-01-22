//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "MenuSystem.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CMenuSystem::CMenuSystem(tle::I3DEngine* pMyEngine, int horiz, int vert, bool fullscreen) :
	mpMyEngine{ pMyEngine }, mHorizWindowSize{horiz}, mVertWindowSize{vert}, mFullscreen{fullscreen}
{
	// We always want control of the mouse pointer when we have a menu open
	mpMyEngine->StopMouseCapture();
}


CMenuSystem::~CMenuSystem()
{
}


//-----------------------------------------------------------------------------
//---- Protected Methods ------------------------------------------------------
//-----------------------------------------------------------------------------

// Update the current location of the mouse with relation to the top left of the window/fullscreen
void CMenuSystem::UpdateMousePos()
{
	mMouseX = mpMyEngine->GetMouseX();
	mMouseY = mpMyEngine->GetMouseY();
}

// Create the sprite and add the struct of details to the button vector
void CMenuSystem::CreateButton(const MenuButton & button)
{
	std::unique_ptr<MenuOption> option = make_unique<MenuOption>();
	option->fileName = button.fileName;
	option->button = mpMyEngine->CreateSprite(
		button.fileName,
		button.xPos * mHorizWindowSize - button.radius,
		button.yPos * mVertWindowSize - button.radius,
		0.1f);
	option->radius = button.radius;

	mMenuOptions.push_back(move(option));
}
