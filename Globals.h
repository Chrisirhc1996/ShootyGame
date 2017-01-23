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
	".\\Media",
	".\\Media\\spaceship"
};


//////////////
//	Media	//
//////////////

const string BORDER = "blueBorder.png";
const string SPACESHIP_MESH = "FFstarfighter.x";

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
const MenuButton QUIT_TO_MENU{ "quitbutton.png", 50.0f, 0.9f, 0.9f };


//////////////////
//	Constants	//
//////////////////

const float PLAYER_SPEED = 15.0f;
const float PLAYER_MIN_X = -80.0f;
const float PLAYER_MAX_X = 30.0f;
const float PLAYER_MIN_Y = -40.0f;
const float PLAYER_MAX_Y = 40.0f;

//////////////////
// Key bindings //
//////////////////

// System
const tle::EKeyCode ESCAPE = tle::Key_Escape;
const tle::EKeyCode PAUSE = tle::Key_P;
const tle::EKeyCode SELECT = tle::Mouse_LButton;

// Player Controls
const tle::EKeyCode UP = tle::Key_W;
const tle::EKeyCode DOWN = tle::Key_S;
const tle::EKeyCode LEFT = tle::Key_A;
const tle::EKeyCode RIGHT = tle::Key_D;