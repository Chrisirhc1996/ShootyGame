//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "MenuSystem.h"
#include <D3D11.h>

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CMenuSystem::CMenuSystem(CResourceManager* pResources, MenuStates& menuState, int horiz, int vert, bool fullscreen) :
	mpResources{ pResources }, mMenuState{ menuState },  mHorizWindowSize { horiz },
	mVertWindowSize{ vert }, mFullscreen{ fullscreen }
{
	// We always want control of the mouse pointer when we have a menu open
	mpResources->GetEngine()->StopMouseCapture();
}


CMenuSystem::~CMenuSystem()
{
	for (auto& option : mMenuOptions)
	{
		mpResources->GetQuadMesh()->RemoveModel(option->button);
	}
}


//-----------------------------------------------------------------------------
//---- Protected Methods ------------------------------------------------------
//-----------------------------------------------------------------------------

// Update the current location of the mouse with relation to the top left of the window/fullscreen
void CMenuSystem::UpdateMousePos()
{
	mMouseX = mpResources->GetEngine()->GetMouseX();
	mMouseY = mpResources->GetEngine()->GetMouseY();
}

// Create the sprite and add the struct of details to the button vector
void CMenuSystem::CreateButton(const MenuButton & button)
{
	std::unique_ptr<SMenuOption> option = make_unique<SMenuOption>();
	option->fileName = button.fileName;
	option->button = mpResources->GetQuadMesh()->CreateModel(
		button.xPos, button.yPos, button.zPos);
	option->button->SetSkin(button.fileName);
	option->radius = button.radius;
	option->screenX = button.screenX;
	option->screenY = button.screenY;

	mMenuOptions.push_back(move(option));
}

// Do cursor collision detection on the buttons
void CMenuSystem::SelectMenuOption(GameStates& state)
{
	// Active menu buttons
	if (mpResources->GetEngine()->KeyHit(SELECT))
	{
		int heightAdjustment = 0;
		int widthAdjustment = 0;
		if (mFullscreen)
		{
			heightAdjustment = (mVertWindowSize / 1000) * 30;
			widthAdjustment = mVertWindowSize / 200;
		}

		// Go through each menu option
		for (auto& option : mMenuOptions)
		{
			// Use raycasting.... no access to required info 
			// 
			// Let's cheat instead :)
			//-----------------------------------------------------------------
			// Do we need adjustments???

			// - static_cast<float>(widthAdjustment);
			// - static_cast<float>(heightAdjustment);

			float buttonXPos = option->screenX * mHorizWindowSize;
			float buttonYPos = option->screenY * mVertWindowSize;


			// Vector from pointer to button centre
			float x = buttonXPos - static_cast<float>(mMouseX);
			float y = buttonYPos - static_cast<float>(mMouseY);

			// Distance from the pointer to the button centre
			float distance = sqrtf(x*x + y*y);

			// If the mouse pointer is in collision with the menu options
			if (distance < option->radius * mHorizWindowSize)
			{		
				// Main menu selections
				if (mMenuState == MenuStates::MAIN_MENU)
				{
					if (option->fileName == PLAY.fileName)
					{
						mpResources->GetEngine()->StartMouseCapture();
						state = GameStates::PLAYING;
						break;
					}
					else if (option->fileName == OPTIONS.fileName)
					{
						//mMenuState = MenuStates::OPTIONS_MENU;
						break;
					}
					else if (option->fileName == QUIT.fileName)
					{
						mpResources->GetEngine()->Stop();
						break;
					}
				}
				// In-game pause menu
				else if (mMenuState == MenuStates::PAUSE_MENU)
				{
					if (option->fileName == UNPAUSE.fileName)
					{
						mpResources->GetEngine()->StartMouseCapture();
						state = GameStates::PLAYING;
						break;
					}
					else if (option->fileName == PAUSE_OPTIONS.fileName)
					{
						//mMenuState = MenuStates::OPTIONS_MENU;
						break;
					}
					else if (option->fileName == QUIT_TO_MENU.fileName)
					{
						state = GameStates::MENU;
						mMenuState = MenuStates::MAIN_MENU;
						break;
					}
				}
			}
		}
	}
	else if (mMenuState == MenuStates::PAUSE_MENU &&
		(mpResources->GetEngine()->KeyHit(PAUSE) ||
		mpResources->GetEngine()->KeyHit(ESCAPE)))
	{
		// Unpaused using pause key or escape key while on pause menu
		mpResources->GetEngine()->StartMouseCapture();
		state = GameStates::PLAYING;
	}
	else if (mMenuState == MenuStates::MAIN_MENU &&
		mpResources->GetEngine()->KeyHit(ESCAPE))
	{
		// Exit the game while on main menu when hitting the escape key
		mpResources->GetEngine()->Stop();
	}
}