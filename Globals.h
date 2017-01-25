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
	".\\Media\\spaceship",
	".\\Media\\Particles"
};


//////////////
//	Media	//
//////////////

const string BORDER = "blueBorder.png";
const string SPACESHIP_MESH = "FFstarfighter.x";
const string BULLET_SPRITE = "Bullet.png";
const string PARTICLE_MESH = "particle.x";
const string QUAD_MESH = "quad.x";


//////////////
//	Menu	//
//////////////

struct MenuButton
{
	string fileName;	// For the skin
	float radius;		// Multiplied by the window Y resolution
	float xPos;			// Position in world space
	float yPos;			// Position in world space
	float zPos;			// Position in world space
	float screenX;		// Position on the screen. Multiplied by the window X resolution
	float screenY;		// Position on the screen. Multiplied by the window Y resolution
};

// Main menu buttons
const MenuButton PLAY{ "playbutton.png", 0.0293f, 0.0f, 20.0f, 0.0f, 0.5f, 0.289f };
const MenuButton OPTIONS{ "optionbutton.png", 0.0293f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f };
const MenuButton QUIT{ "quitbutton.png", 0.0293f, 0.0f, -20.0f, 0.0f, 0.5f, 0.712f };

// Pause menu buttons
const MenuButton UNPAUSE{ "playbutton.png", 0.0293f, 20.0f, -35.0f, 0.0f, 0.619f, 0.8725f };
const MenuButton PAUSE_OPTIONS{ "optionbutton.png", 0.0293f, 40.0f, -35.0f, 0.0f, 0.735f, 0.8725f };
const MenuButton QUIT_TO_MENU{ "quitbutton.png", 0.0293f, 60.0f, -35.0f, 0.0f, 0.856f, 0.8725f };


//////////////////
//	Constants	//
//////////////////

const float CAMERA_Z = -100.0f;

const float PLAYER_SPEED = 20.0f;
const float PLAYER_START_X = -60.0f;
const float PLAYER_START_Y = 0.0f;
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