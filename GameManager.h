#pragma once

// Dependencies
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <memory>
#include "MenuSystem.h"
#include "Globals.h"

class CGameManager
{
private:
	// Variables //

	tle::I3DEngine* mpMyEngine;
	tle::ICamera* mpMyCamera;

	int mHorizontal;				// desktop X resolution
	int mVertical;					// desktop Y resolution

	bool mFullscreen = false;

	float mFrameTime;				// the time in seconds since the last update

	GameStates mGameState = GameStates::MENU;		// overall state of the game, i.e. playing, paused or in the menu	
	MenuStates mMenuState = MenuStates::MAIN_MENU;	// states which menu we are in
	std::unique_ptr<CMenuSystem> mpMenu;			// handle for the menu system

public:
	// Constructor
	CGameManager();
	//  Destructor
	~CGameManager();

	// Main game loop, the game ends when this exits
	void RunGame();

private:
	// Private Methods //

	// Get the horizontal and vertical screen sizes in pixel
	void GetDesktopResolution(int& horizontal, int& vertical);
	bool CreateEngine();
	void AddMediaFolders();
	// if the game loses focus(minimised etc) and if in a game, the game will be paused 
	// and the pause menu created.  Always returns the mouse cursor to the user
	void inactiveWindowControl();
};