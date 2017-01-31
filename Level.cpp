//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Level.h"

#include "Globals.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CLevel::CLevel(CResourceManager* pResources) :
	mpResources{ pResources }
{
	// Create UI
	mpUIBorder = mpResources->GetQuadMesh()->CreateModel(-4.0f, 0.0f, -95.0f);
	mpUIBorder->RotateX(180.0f);
	mpUIBorder->SetSkin(BORDER);
	mpUIBorder2 = mpResources->GetQuadMesh()->CreateModel(4.0f, 0.0f, -95.0f);
	mpUIBorder2->RotateY(180.0f);
	mpUIBorder2->SetSkin(BORDER);

	// Create player
	mpPlayer = std::make_unique<CPlayer>(mpResources);

	//TEMP....
	// Create an enemy
	mEnemies.push_back(std::make_unique<CEnemy>(mpResources));
}


CLevel::~CLevel()
{
	// Cleanup sprites
	mpResources->GetQuadMesh()->RemoveModel(mpUIBorder);
	mpResources->GetQuadMesh()->RemoveModel(mpUIBorder2);
}

// Play the current level  (Loop)
void CLevel::PlayLevel(float frameTime)
{
	////////////////////
	// Player actions //
	mpPlayer->Move(frameTime);

	if (mpResources->GetEngine()->KeyHeld(tle::Key_Space))
	{
		// Shoot when space is pressed
		mpPlayer->GetWeaponSystem()->ShootWeapon(mpPlayer->GetXPos(), mpPlayer->GetYPos());
	}
	mpPlayer->GetWeaponSystem()->MoveWeaponParticles(frameTime);

	// Collision detection between players weapon output and enemies
	std::vector<CEnemy*> deadEnemies;
	for (auto& enemy : mEnemies)
	{
		if (mpPlayer->GetWeaponSystem()->CollisionCheck(enemy.get()))
		{
			// Enemy hit!
			deadEnemies.push_back(enemy.get());
		}
	}
	for (auto& deleteThis : deadEnemies)
	{
		// Find the matching unique_ptr
		auto i = mEnemies.begin();
		auto e = mEnemies.end();
		while (i != e)
		{
			if (deleteThis == i->get())
				i = mEnemies.erase(i);
			else
				++i;
		}
	}

	///////////////////
	// Enemy actions //
	for (auto& enemy : mEnemies)
	{
		// Shoot continously
		enemy->GetWeaponSystem()->ShootWeapon(enemy->GetXPos(), enemy->GetYPos());
		enemy->GetWeaponSystem()->MoveWeaponParticles(frameTime);
	}
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------
