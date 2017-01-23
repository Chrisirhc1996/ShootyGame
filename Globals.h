#pragma once

#include <TL-Engine.h>
#include <string>


//////////////
//	States	//
//////////////

enum class GameStates
{
	PLAYING,
	PAUSED,
	MENU
};

enum class MenuStates
{
	MAIN_MENU,
	OPTIONS_MENU,
	PAUSE_MENU
};


//////////////////////
//	Media Folders	//
//////////////////////

const std::string MEDIA_FOLDERS[] = {
	".\\Media"
};


//////////////
//	Media	//
//////////////


//////////////
//	Menu	//
//////////////

struct MenuButton
{
	string fileName;
	float radius;
	float xPos;
	float yPos;
};

// x and y positions are multiplied by the window resolution

// Main menu buttons
const MenuButton PLAY{ "playbutton.png", 50.0f, 0.5f, 0.3f };
const MenuButton OPTIONS{ "optionbutton.png", 50.0f, 0.5f, 0.5f };
const MenuButton QUIT{ "quitbutton.png", 50.0f, 0.5f, 0.7f };

// Pause menu buttons
const MenuButton UNPAUSE{ "playbutton.png", 50.0f, 0.8f, 0.9f };
const MenuButton PAUSE_OPTIONS{ "optionbutton.png", 50.0f, 0.85f, 0.9f };
const MenuButton PAUSE_QUIT{ "quitbutton.png", 50.0f, 0.9f, 0.9f };


//////////////////
//	Constants	//
//////////////////


//////////////////
// Key bindings //
//////////////////

// System
const tle::EKeyCode ESCAPE = tle::Key_Escape;
const tle::EKeyCode PAUSE = tle::Key_P;
const tle::EKeyCode SELECT = tle::Mouse_LButton;