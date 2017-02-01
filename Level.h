#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include <list>

class CResourceManager;
class CPlayer;
class CEnemy;
class CAmmo;


class CLevel
{
private:
	// Variables //

	CResourceManager* mpResources;
	
	tle::IModel* mpUIBorder;
	tle::IModel* mpUIBorder2;

	std::unique_ptr<CPlayer> mpPlayer;
	std::list<std::unique_ptr<CEnemy>> mEnemies;

	std::list<std::unique_ptr<CAmmo>> mAmmo;			// All bullets, laser beams etc, on the screen
	std::list<std::unique_ptr<CAmmo>> mResetBullets;	// Bullets waiting to be reused

	float mBackgroundSpeed;			// Scroll speed

public:
	// Constructor
	CLevel(CResourceManager* pResources);
	//  Destructor	
	~CLevel();

	// Play the current level
	bool PlayLevel(float frameTime);

private:
	// Private Methods //

	// Check collisions
	bool CollisionCheckEnemies(CEnemy* enemy);
	bool CollisionCheckPlayer(CPlayer* player);

	void ScrollingBackground();
};

