//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "GameManager.h"
#include "MainMenu.h"
#include "wtypes.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CGameManager::CGameManager()
{
	//If something went wrong, cancel the construction of the game
	if (!CreateEngine())
		throw;

	// provide the search paths for any media used
	AddMediaFolders();

	// Create the main default camera
	mpMyCamera = mpMyEngine->CreateCamera();

	// create the main menu straight away
	mpMenu = std::make_unique<CMainMenu>(mpMyEngine, mMenuState, mHorizontal, mVertical, mFullscreen);

	// initialise the frame timer
	mFrameTime = mpMyEngine->Timer();
}


CGameManager::~CGameManager()
{
	// Delete the 3D engine now we are finished with it
	mpMyEngine->Delete();
}

// Main game loop, the game ends when this exits
void CGameManager::RunGame()
{
	// The main game loop, repeat until engine is stopped
	while (mpMyEngine->IsRunning())
	{
		// Draw the scene
		mpMyEngine->DrawScene();

		// Update the frame time
		mFrameTime = mpMyEngine->Timer();

		// true when the window is in the foreground and selected
		if (mpMyEngine->IsActive())
		{
			// GAME CODE HERE...
		}
		else if (mGameState == GameStates::PLAYING)
		{
			inactiveWindowControl();
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

bool CGameManager::CreateEngine()
{
	// Create a 3D engine
	mpMyEngine = tle::New3DEngine(tle::kTLX);

	if (!mpMyEngine)
		return false;

	GetDesktopResolution(mHorizontal, mVertical);

	//Open the game window
	mpMyEngine->StartWindowed(mHorizontal, mVertical);
	mFullscreen = false;
	/*myEngine->StartFullscreen(mHorizontal, mVertical);
	mFullscreen = true;*/

	return true;
}

void CGameManager::AddMediaFolders()
{
	// Add folders for meshes and other media
	for (int i = 0; i < sizeof(MEDIA_FOLDERS) / sizeof(MEDIA_FOLDERS[0]); ++i)
	{
		mpMyEngine->AddMediaFolder(MEDIA_FOLDERS[i]);
	}
}

void CGameManager::inactiveWindowControl()
{
	// if the window loses focus during a gam
	mGameState = GameStates::PAUSED;

	//menu = new PauseMenu();

	mpMyEngine->StopMouseCapture();	// return the mouse cursor so the menu can be operated
}
