//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "GameManager.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "wtypes.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CGameManager::CGameManager()
{
	//// Load the engine and meshes
	//mpResources = CResourceManager::getInstance();
	//mpResources->LoadResources();

	mpResources = std::make_unique<CResourceManager>();

	// Create the window of the size of the screen
	CreateScreen();

	// provide the search paths for any media used
	AddMediaFolders();

	mpResources->LoadResources();

	// create the main menu straight away
	mpMenu = std::make_unique<CMainMenu>(mpResources.get(), mMenuState, mHorizontal, mVertical, mFullscreen);

	// initialise the frame timer
	mFrameTime = mpResources->GetEngine()->Timer();
}


CGameManager::~CGameManager()
{
	// Cleanup the level if not already done
	if (mpLevel)
		mpLevel.reset();

	// Cleanup the menu if not already done
	if (mpMenu)
		mpMenu.reset();
}

// Main game loop, the game ends when this exits
void CGameManager::RunGame()
{
	// The main game loop, repeat until engine is stopped
	while (mpResources->GetEngine()->IsRunning())
	{
		// Draw the scene
		mpResources->GetEngine()->DrawScene();

		// Update the frame time
		mFrameTime = mpResources->GetEngine()->Timer();

		// true when the window is in the foreground and selected
		if (mpResources->GetEngine()->IsActive())
		{		

			if (mGameState == GameStates::PLAYING)
			{
				if (mpResources->GetEngine()->KeyHit(PAUSE) ||
					mpResources->GetEngine()->KeyHit(ESCAPE))
				{
					PauseGame();
				}

				//--------------------------------------------------------
				// GAME CODE HERE...
				//--------------------------------------------------------
				mpLevel->PlayLevel(mFrameTime);
			}

			if (mGameState == GameStates::MENU)
			{
				mpMenu->ButtonPresses(mGameState);
				
				if (mGameState == GameStates::PLAYING)
				{
					// Release the memory in the unique pointer removing the menu
					mpMenu.reset();
					
					// Create the level
					mpLevel = std::make_unique<CLevel>(mpResources.get());
				}
			}
			else if (mGameState == GameStates::PAUSED)
			{
				mpMenu->ButtonPresses(mGameState);
	 
				if (mGameState == GameStates::PLAYING)
				{
					// Release the memory in the unique pointer removing the menu
					mpMenu.reset();
				}

				if (mGameState == GameStates::MENU)
				{
					// The player has exited back to the main menu

					// Delete the game level as no longer need it
					mpLevel.reset();
					// Recreate the main menu
					mpMenu = std::make_unique<CMainMenu>(mpResources.get(), mMenuState, mHorizontal, mVertical, mFullscreen);
				}
			}
		}
		else if (mGameState == GameStates::PLAYING)
		{
			InactiveWindowControl();
		}
	}
}

//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------

// Get the horizontal and vertical screen sizes in pixel
void CGameManager::GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();

	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);

	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void CGameManager::CreateScreen()
{
	GetDesktopResolution(mHorizontal, mVertical);

	//Open the game window
	mpResources->GetEngine()->StartWindowed(mHorizontal, mVertical);
	mFullscreen = false;
	//mpResources->GetEngine()->StartFullscreen(mHorizontal, mVertical);
	//mFullscreen = true;
}

void CGameManager::AddMediaFolders()
{
	// Add folders for meshes and other media
	for (int i = 0; i < sizeof(MEDIA_FOLDERS) / sizeof(MEDIA_FOLDERS[0]); ++i)
	{
		mpResources->GetEngine()->AddMediaFolder(MEDIA_FOLDERS[i]);
	}
}

// Bring up the pause menu
void CGameManager::PauseGame()
{
	// if the window loses focus during a game
	mGameState = GameStates::PAUSED;
	mMenuState = MenuStates::PAUSE_MENU;

	mpMenu = std::make_unique<CPauseMenu>(mpResources.get(), mMenuState, mHorizontal, mVertical, mFullscreen);

	mpResources->GetEngine()->StopMouseCapture();	// return the mouse cursor so the menu can be operated
}

void CGameManager::InactiveWindowControl()
{
	PauseGame();
}
