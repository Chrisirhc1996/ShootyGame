//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "MenuSystem.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CMenuSystem::CMenuSystem(tle::I3DEngine* pMyEngine, MenuStates& menuState, int horiz, int vert, bool fullscreen) :
	mpMyEngine{ pMyEngine }, mMenuState{ menuState },  mHorizWindowSize { horiz }, 
	mVertWindowSize{ vert }, mFullscreen{ fullscreen }
{
	// We always want control of the mouse pointer when we have a menu open
	mpMyEngine->StopMouseCapture();
}


CMenuSystem::~CMenuSystem()
{
	for (auto& option : mMenuOptions)
	{
		mpMyEngine->RemoveSprite(option->button);
	}
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
	std::unique_ptr<SMenuOption> option = make_unique<SMenuOption>();
	option->fileName = button.fileName;
	option->button = mpMyEngine->CreateSprite(
		button.fileName,
		button.xPos * mHorizWindowSize - button.radius,
		button.yPos * mVertWindowSize - button.radius,
		0.1f);
	option->radius = button.radius;

	mMenuOptions.push_back(move(option));
}

// Do cursor collision detection on the buttons
void CMenuSystem::SelectMenuOption(GameStates& state)
{
	int heightAdjustment = 0;
	int widthAdjustment = 0;
	if (mFullscreen)
	{
		heightAdjustment = (mVertWindowSize / 1000) * 30;
		widthAdjustment = mVertWindowSize / 200;
	}

	int index = 0;

	// Go through each menu option
	for (auto& option : mMenuOptions)
	{
		float buttonXPos = option->button->GetX() + option->radius - static_cast<float>(widthAdjustment);
		float buttonYPos = option->button->GetY() + option->radius - static_cast<float>(heightAdjustment);

		// Vector from pointer to button centre
		float x = buttonXPos - static_cast<float>(mMouseX);
		float y = buttonYPos - static_cast<float>(mMouseY);

		// Distance from the pointer to the button centre
		float distance = sqrtf(x*x + y*y);

		// If the mouse pointer is in collision with the menu options
		if (distance < option->radius)
		{
			// Active menu buttons
			if (mpMyEngine->KeyHit(SELECT))
			{
				// Main menu selections
				if (mMenuState == MenuStates::MAIN_MENU)
				{
					if (option->fileName == PLAY.fileName)
					{
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
						mpMyEngine->Stop();
						break;
					}
				}
				// In-game pause menu
				else if (mMenuState == MenuStates::PAUSE_MENU)
				{
					if (option->fileName == UNPAUSE.fileName)
					{
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
}