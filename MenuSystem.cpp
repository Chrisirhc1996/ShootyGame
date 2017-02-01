//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "MenuSystem.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CMenuSystem::CMenuSystem(CResourceManager* pResources, MenuStates& menuState, int horiz, int vert, bool fullscreen) :
	mpResources{ pResources }, mMenuState{ menuState },  mHorizWindowSize { horiz },
	mVertWindowSize{ vert }, mFullscreen{ fullscreen }
{
	// We always want control of the mouse pointer when we have a menu open
	mpResources->GetEngine()->StopMouseCapture();
	mpResources->GetCamera()->SetNearClip(nearClip);
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

	mMenuOptions.push_back(move(option));
}

// Return the world point under the mouse with the given z-distance from the camera
CVector3 CMenuSystem::PointFromMouse(float cameraZDist)
{
	CVector3 mousePoint = WorldPointFromPixel(mpResources->GetEngine()->GetMouseX(),
		mpResources->GetEngine()->GetMouseY(), mpResources->GetCamera(), nearClip, mpResources->GetEngine());
	CVector3 mouseRay = NormaliseVector(mousePoint - CameraPosition(mpResources->GetCamera()));
	float rayDistance = cameraZDist / Dot(mouseRay, CameraFacing(mpResources->GetCamera()));
	return CameraPosition(mpResources->GetCamera()) + mouseRay * rayDistance;
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

		CVector3 worldPos = PointFromMouse(-CAMERA_Z);

		// Go through each menu option
		for (auto& option : mMenuOptions)
		{
			// If the mouse pointer is in collision with the menu options
			if (fabs(option->button->GetX() - worldPos.x) < option->radius &&
				fabs(option->button->GetY() - worldPos.y) < option->radius)
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