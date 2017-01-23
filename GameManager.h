#pragma once

// Dependencies
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <memory>
#include "MenuSystem.h"
#include "Level.h"
#include "Globals.h"

class CGameManager
{
private:
	// Variables //

	tle::I3DEngine* mpMyEngine;
	tle::ICamera* mpMyCamera;

	tle::IMesh* mpPlayerMesh;

	int mHorizontal;				// Desktop X resolution
	int mVertical;					// Desktop Y resolution

	bool mFullscreen = false;

	float mFrameTime;				// The time in seconds since the last update

	GameStates mGameState = GameStates::MENU;		// Overall state of the game, i.e. playing, paused or in the menu	
	MenuStates mMenuState = MenuStates::MAIN_MENU;		// States which menu we are in
	std::unique_ptr<CMenuSystem> mpMenu;			// Handle for the menu system
	std::unique_ptr<CLevel> mpLevel;			// Handle for the game level

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
	// Bring up the pause menu
	void PauseGame();
	// If the game loses focus(minimised etc) and if in a game, the game will be paused 
	// and the pause menu created.  Always returns the mouse cursor to the user
	void InactiveWindowControl();
};
