#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include <vector>
#include "Globals.h"
#include "ResourceManager.h"
#include "Support.h"

class CMenuSystem
{
private:
	// Variables //
	CResourceManager* mpResources;

	MenuStates& mMenuState;

	int mMouseX = 0;
	int mMouseY = 0;

	int mHorizWindowSize;
	int mVertWindowSize;
	bool mFullscreen;

	float nearClip = 1.0f;

	struct SMenuOption
	{
		string fileName;
		tle::IModel* button;
		float radius;
	};

	std::vector<std::unique_ptr<SMenuOption>> mMenuOptions;	// holds all buttons currently created


public:
	// Constructor
	CMenuSystem(CResourceManager* pResources, MenuStates& menuState, int horiz, int vert, bool fullscreen);
	//  Destructor
	virtual ~CMenuSystem();

	virtual void ButtonPresses(GameStates& state) = 0;


protected:
	// Protected Methods //

	// Update the current location of the mouse with relation to the top left of the window/fullscreen
	void UpdateMousePos();
	// Create the sprite and add the struct of details to the button vector
	void CreateButton(const MenuButton& button);
	// Return the world point under the mouse with the given z-distance from the camera
	CVector3 PointFromMouse(float cameraZDist);;
	// Do cursor collision detection on the buttons
	void SelectMenuOption(GameStates& state);

	// Getters
	const MenuStates& GetMenuState() const { return mMenuState; }

	// Setters
	void SetMenuState(MenuStates& state) { mMenuState = state; }
};