//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Blaster.h"

#include "Bullet.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CBlaster::CBlaster(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList, bool enemyShooting) :
	CWeapon(pResources, enemyShooting), mAmmoList{ ammoList }
{
	mLifetime = 4.0f;
	mRateOfFire = 0.2f;
	if (enemyShooting)
		mSpeed = -60.0f;
	else
		mSpeed = 60.0f;
}


CBlaster::~CBlaster()
{
}



void CBlaster::ShootWeapon(float xPos, float yPos)
{
	if (mFiringTimer > mRateOfFire)
	{
		mFiringTimer = 0.0f;
		CreateBullet(xPos, yPos);
	}
}

//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------

void CBlaster::CreateBullet(float xPos, float yPos)
{
	// If we have bullets already made and in reserve, move a bullet from the reserse to the active list
	if (CBlaster::mResetBullets.size() != 0)
	{
		CBlaster::mResetBullets.back()->SetFromEnemy(IsEnemyWeapon());
		CBlaster::mResetBullets.back()->SetSpeed(mSpeed);
		CBlaster::mResetBullets.back()->SetLifetime(mLifetime);
		CBlaster::mResetBullets.back()->GetModel()->SetPosition(xPos, yPos, 0.0f);
		mAmmoList.push_front(move(CBlaster::mResetBullets.back()));
		CBlaster::mResetBullets.pop_back();
	}
	else
		// Create a new bullet from scratch
		mAmmoList.push_front(std::make_unique<CBullet>(GetResources(), mLifetime, mSpeed, xPos, yPos, IsEnemyWeapon()));
}


//------------------------------------------------------------------------------------------
// The static reserved list for expired bullets specifically
std::list<std::unique_ptr<CAmmo>> CBlaster::mResetBullets;