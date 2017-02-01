#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include <list>
#include <vector>

class CResourceManager;
class CEntity;
class CPlayer;
class CEnemy;
class CAmmo;


class CLevel
{
private:
	// Variables //

	CResourceManager* mpResources;
	
	tle::IModel* mpBackgroundParent;			// Used to move the whole background as one
	std::vector<tle::IModel*> mBackground;		// The full background spanning multiple screens

	std::unique_ptr<CPlayer> mpPlayer;
	std::list<std::unique_ptr<CEnemy>> mEnemies;

	std::list<std::unique_ptr<CAmmo>> mAmmo;			// All bullets, laser beams etc, on the screen
	std::list<std::unique_ptr<CAmmo>> mResetBullets;	// Bullets waiting to be reused
	std::list<std::unique_ptr<CAmmo>> mResetBeams;		// Laser beams waiting to be reused

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
	bool CollisionCheck(CEntity* pTargetEntity, bool isEnemy);

	void ScrollingBackground(float frameTime);
};

