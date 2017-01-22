#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include <vector>
#include "Globals.h"

class CMenuSystem
{
private:
	// Variables //
	tle::I3DEngine* mpMyEngine;

	MenuStates mMenuState;

	int mMouseX = 0;
	int mMouseY = 0;

	int mHorizWindowSize;
	int mVertWindowSize;
	bool mFullscreen;

	struct MenuOption
	{
		string fileName;
		tle::ISprite* button;
		float radius;
	};

	std::vector<std::unique_ptr<MenuOption>> mMenuOptions;	// holds all buttons currently created

public:
	// Constructor
	CMenuSystem(tle::I3DEngine* pMyEngine, int horiz, int vert, bool fullscreen);
	//  Destructor
	~CMenuSystem();

protected:
	// Protected Methods //

	// Update the current location of the mouse with relation to the top left of the window/fullscreen
	void UpdateMousePos();
	// Create the sprite and add the struct of details to the button vector
	void CreateButton(const MenuButton& button);

	// Getters
	const MenuStates& GetMenuState() const { return mMenuState; }

	// Setters
	void SetMenuState(MenuStates& state) { mMenuState = state; }
};

