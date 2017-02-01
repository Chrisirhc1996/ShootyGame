//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Level.h"

#include "Globals.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Blaster.h"

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
	mpPlayer = std::make_unique<CPlayer>(mpResources, mAmmo);

	//TEMP....
	// Create an enemy
	mEnemies.push_back(std::make_unique<CEnemy>(mpResources, mAmmo));
}


CLevel::~CLevel()
{
	// Cleanup remaining models
	mpResources->GetQuadMesh()->RemoveModel(mpUIBorder);
	mpResources->GetQuadMesh()->RemoveModel(mpUIBorder2);

	for (auto& ammo : mAmmo)
	{
		mpResources->GetQuadMesh()->RemoveModel(ammo->GetModel());
	}
	for (auto& ammo : CBlaster::GetBulletReserve())
	{
		mpResources->GetQuadMesh()->RemoveModel(ammo->GetModel());
	}
	CBlaster::GetBulletReserve().clear();
}

// Play the current level  (Loop)
bool CLevel::PlayLevel(float frameTime)
{
	////////////////////
	// Player actions //
	mpPlayer->Move(frameTime);

	if (mpResources->GetEngine()->KeyHeld(tle::Key_Space))
	{
		// Shoot when space is pressed
		mpPlayer->GetWeaponSystem()->ShootWeapon(mpPlayer->GetXPos(), mpPlayer->GetYPos());
	}
	mpPlayer->GetWeaponSystem()->UpdateTimer(frameTime);

	///////////////////
	// Enemy actions //
	for (auto& enemy : mEnemies)
	{
		// Shoot continously
		enemy->GetWeaponSystem()->ShootWeapon(enemy->GetXPos(), enemy->GetYPos());
		enemy->GetWeaponSystem()->UpdateTimer(frameTime);
	}

	//////////////////////////////////////////////////////////////////////////
	// Move all the bullets on the screen, if expired push to reserved list //
	std::vector<CAmmo*> ammoRecycler;
	for (auto& weaponDischarge : mAmmo)
	{
		if (weaponDischarge->Move(frameTime))
		{
			// Expired and must be recycled
			ammoRecycler.push_back(weaponDischarge.get());
		}
	}
	for (auto& moveThis : ammoRecycler)
	{
		// Find the matching unique_ptr
		auto i = mAmmo.begin();
		auto end = mAmmo.end();

		while (i != end)
		{
			if (moveThis == i->get())
			{
				if (moveThis->GetAmmoType() == BULLETS)
					CBlaster::GetBulletReserve().push_back(move(*i));
				else if (moveThis->GetAmmoType() == LASERS)
				{/* for when lasers get implimented */}
				else if (moveThis->GetAmmoType() == ROCKETS)
				{/* for when rockets get implimented */}
				else if (moveThis->GetAmmoType() == PLASMA)
				{/* for when plasma gets implimented */}

				i = mAmmo.erase(i);
			}
			else
				++i;
		}
	}

	///////////////////////////////////////////////////////////////////
	// Collision detection between players weapon output and enemies //
	std::vector<CEnemy*> deadEnemies;
	for (auto& enemy : mEnemies)
	{
		if (CollisionCheckEnemies(enemy.get()))
		{
			// Enemy hit!
			deadEnemies.push_back(enemy.get());
		}
	}
	for (auto& deleteThis : deadEnemies)
	{
		// Find the matching unique_ptr
		auto i = mEnemies.begin();
		auto end = mEnemies.end();

		while (i != end)
		{
			if (deleteThis == i->get())
				i = mEnemies.erase(i);
			else
				++i;
		}
	}

	//////////////////////////////////////////////////////////////////////
	// Collision detection between enemies weapon output and the player //
	if (CollisionCheckPlayer(mpPlayer.get()))
	{
		// Player hit!

		// Deduct a life and check how many left
		if (mpPlayer->LoseALife() <= 0)
		{
			// Game over!
			return false;
		}
	}
	return true;
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------

bool CLevel::CollisionCheckEnemies(CEnemy* enemy)
{
	for (auto& bullet : mAmmo)
	{
		if (!bullet->FromEnemy())
		{
			if (fabs(bullet->GetXPos() - enemy->GetXPos()) < 5.0f/*half model length*/ &&
				fabs(bullet->GetYPos() - enemy->GetYPos()) < 2.0f/*half model height*/)
			{
				// Theres been a collision!

				// Get the bullet out of the way as if destroyed where it will wait to expire and be recycled
				bullet->SetYPos(1000.0f);
				return true;
			}
		}
	}
	return false;
}

bool CLevel::CollisionCheckPlayer(CPlayer* player)
{
	for (auto& bullet : mAmmo)
	{
		if (bullet->FromEnemy())
		{
			if (fabs(bullet->GetXPos() - player->GetXPos()) < 5.0f/*half model length*/ &&
				fabs(bullet->GetYPos() - player->GetYPos()) < 2.0f/*half model height*/)
			{
				// Theres been a collision!

				// Get the bullet out of the way as if destroyed where it will wait to expire and be recycled
				bullet->SetYPos(1000.0f);
				return true;
			}
		}
	}
	return false;
}