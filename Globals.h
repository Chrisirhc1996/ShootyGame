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

const string SPACESHIP_MESH = "FFstarfighter.x";
const string PARTICLE_MESH = "particle.x";
const string QUAD_MESH = "quad.x";
const string CUBE_MESH = "Cube.x";
const string DUMMY_MESH = "Dummy.x";

const string BACKGROUND_1 = "tileable-nebula.png";
const string BACKGROUND_2 = "tileable-classic-nebula.jpg";
const string BULLET_SPRITE = "Bullet.png";
const string LASER_SPRITE = "beam.jpg";
const string PLASMA_SPRITE = "012_tlxadd.tga";
const string ROCKET_SPRITE = "011_tlxadd.tga";


//////////////
//	Menu	//
//////////////

struct MenuButton
{
	string fileName;	// For the skin
	float radius;		// Radius of the model in world space
	float xPos;			// Position in world space
	float yPos;			// Position in world space
	float zPos;			// Position in world space
};

// Main menu buttons
const MenuButton PLAY{ "playbutton.png", 5.0f, 0.0f, 20.0f, 0.0f };
const MenuButton OPTIONS{ "optionbutton.png", 5.0f, 0.0f, 0.0f, 0.0f };
const MenuButton QUIT{ "quitbutton.png", 5.0f, 0.0f, -20.0f, 0.0f };

// Pause menu buttons
const MenuButton UNPAUSE{ "playbutton.png", 5.0f, 20.0f, -35.0f, 0.0f };
const MenuButton PAUSE_OPTIONS{ "optionbutton.png", 5.0f, 40.0f, -35.0f, 0.0f };
const MenuButton QUIT_TO_MENU{ "quitbutton.png", 5.0f, 60.0f, -35.0f, 0.0f };


//////////////////
//	Constants	//
//////////////////

const float PI = 3.141592741f;

const float CAMERA_Z = -100.0f;

const int BACKGROUND_COUNT = 20;				// How many times does the background tile
const int CUBE_SIZE = 10;						// Used to calculate the spacing between background tiles
const float BACKGROUND_Z = 10.0f;
const float BACKGROUND_SCALE = 12.0f;
const float BACKGROUND_SCROLL_SPEED = 15.0f;

const float PLAYER_SPEED = 20.0f;
const float PLAYER_START_X = -60.0f;
const float PLAYER_START_Y = 0.0f;
const float PLAYER_MIN_X = -80.0f;
const float PLAYER_MAX_X = 30.0f;
const float PLAYER_MIN_Y = -40.0f;
const float PLAYER_MAX_Y = 40.0f;

const float LASER_Z = 5.0f;						// Z position to line up with the ship model
const float LASER_X_OFFSET = 0.6f;				// Multiplied by distance, sets the position in front of the ship

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