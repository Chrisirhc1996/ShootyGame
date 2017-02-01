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
#include "Support.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CLevel::CLevel(CResourceManager* pResources) :
	mpResources{ pResources }
{
	mpBackgroundParent = mpResources->GetDummyMesh()->CreateModel();

	// Create Background
	for (int i = -CUBE_SIZE; i < BACKGROUND_COUNT * CUBE_SIZE; i += CUBE_SIZE)
	{
		tle::IModel* background = mpResources->GetCubeMesh()->CreateModel(
			static_cast<float>(i) * BACKGROUND_SCALE, 0.0f, BACKGROUND_Z);
		background->SetSkin(BACKGROUND_1);
		background->ScaleX(BACKGROUND_SCALE);
		background->ScaleY(BACKGROUND_SCALE);
		background->ScaleZ(0.0f);
		background->AttachToParent(mpBackgroundParent);
		mBackground.push_back(background);
	}

	// Create player
	mpPlayer = std::make_unique<CPlayer>(mpResources, mAmmo, mResetBeams);

	//TEMP....
	// Create an enemy
	mEnemies.push_back(std::make_unique<CEnemy>(mpResources, mAmmo, mResetBeams));
}


CLevel::~CLevel()
{
	// Cleanup remaining models
	for (auto background : mBackground)
	{
		mpResources->GetCubeMesh()->RemoveModel(background);
	}
	mpResources->GetDummyMesh()->RemoveModel(mpBackgroundParent);

	// All ammo
	for (auto& ammo : mAmmo)
	{
		if (ammo->GetAmmoType() == BULLETS)
			mpResources->GetQuadMesh()->RemoveModel(ammo->GetModel());
		else if (ammo->GetAmmoType() == LASERS)
		{
			mpResources->GetQuadMesh()->RemoveModel(ammo->GetBeam());
			mpResources->GetDummyMesh()->RemoveModel(ammo->GetModel());
		}
	}
	for (auto& ammo : mResetBullets)
	{
		mpResources->GetQuadMesh()->RemoveModel(ammo->GetModel());
	}
	for (auto& ammo : mResetBeams)
	{
		mpResources->GetQuadMesh()->RemoveModel(ammo->GetBeam());
		mpResources->GetDummyMesh()->RemoveModel(ammo->GetModel());		
	}
}

// Play the current level  (Loop)
bool CLevel::PlayLevel(float frameTime)
{
	///////////////////////////////////////
	// Scroll the background and objects //
	ScrollingBackground(frameTime);

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

	///////////////////////////////////////////////////////////////////
	// Collision detection between players weapon output and enemies //
	std::vector<CEnemy*> deadEnemies;
	for (auto& enemy : mEnemies)
	{
		if (CollisionCheck(enemy.get(), true))
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
	if (CollisionCheck(mpPlayer.get(), false))
	{
		// Player hit!

		// Deduct a life and check how many left
		if (mpPlayer->LoseALife() <= 0)
		{
			// Game over!
			return false;
		}
	}

	////////////////////////////////////
	// Complete the recycling process //
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
					mResetBullets.push_back(move(*i));
				else if (moveThis->GetAmmoType() == LASERS)
					mResetBeams.push_back(move(*i));
				else if (moveThis->GetAmmoType() == ROCKETS)
				{/* for when rockets get implimented */
				}
				else if (moveThis->GetAmmoType() == PLASMA)
				{/* for when plasma gets implimented */
				}

				i = mAmmo.erase(i);
			}
			else
				++i;
		}
	}

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


	return true;
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------

bool CLevel::CollisionCheck(CEntity* pTargetEntity, bool withEnemy)
{
	float halfWidth = 5.0f;
	float halfHeight = 2.0f;

	if (withEnemy)
	{
		// Players lasers
	}

	for (auto& ammo : mAmmo)
	{
		if (ammo->FromEnemy() != withEnemy)
		{
			float xDistance = 0.0f;
			float yDistance = 0.0f;

			switch (ammo->GetAmmoType())
			{
			case BULLETS:
				xDistance = fabs(ammo->GetXPos() - pTargetEntity->GetXPos());
				yDistance = fabs(ammo->GetYPos() - pTargetEntity->GetYPos());
				break;
			case LASERS:
			{
				CPoint entityPoint(ammo->GetXPos(), ammo->GetYPos() - 1000.0f);
				CPoint laserTip;
				CPoint targetA;
				CPoint targetB;
				if (withEnemy)
				{
					// Players lasers
					laserTip.x = entityPoint.x + static_cast<double>(ammo->GetDistance()) * 5.0;
					laserTip.y = entityPoint.y;
					targetA.x = pTargetEntity->GetXPos() - halfWidth;
					targetA.y = pTargetEntity->GetYPos() - halfHeight;
					targetB.x = pTargetEntity->GetXPos() - halfWidth;
					targetB.y = pTargetEntity->GetYPos() + halfHeight;
				}
				else
				{
					laserTip.x = entityPoint.x + static_cast<double>(ammo->GetDistance()) * -5.0;
					laserTip.y = entityPoint.y;
					targetA.x = pTargetEntity->GetXPos() + halfWidth;
					targetA.y = pTargetEntity->GetYPos() - halfHeight;
					targetB.x = pTargetEntity->GetXPos() + halfWidth;
					targetB.y = pTargetEntity->GetYPos() + halfHeight;
				}
				

				if (!LineCollision(entityPoint, laserTip, targetA, targetB))
				{
					xDistance = 1000.0f;
					yDistance = 1000.0f;
				}
				break;
			}
			case ROCKETS:
				break;
			case PLASMA:
				break;
			default:
				break;
			}
			
			if (xDistance < halfWidth &&
				yDistance < halfHeight)
			{
				// Theres been a collision!

				// Get the bullet out of the way as if destroyed where it will wait to expire and be recycled
				ammo->SetYPos(1000.0f);
				return true;
			}
		}
	}
	return false;
}

void CLevel::ScrollingBackground(float frameTime)
{
	mpBackgroundParent->MoveX(-BACKGROUND_SCROLL_SPEED * frameTime);
}