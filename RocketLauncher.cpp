//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "RocketLauncher.h"

#include "Rocket.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CRocketLauncher::CRocketLauncher(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
	std::list<std::unique_ptr<CAmmo>>& resetRockets, bool enemyShooting) :
	CWeapon(pResources, enemyShooting), mAmmoList{ ammoList }, mResetRockets{ resetRockets }
{
	mLifetime = 4.0f;
	mRateOfFire = 0.2f;
	if (enemyShooting)
		mSpeed = -60.0f;
	else
		mSpeed = 60.0f;
}

CRocketLauncher::~CRocketLauncher()
{
}

void CRocketLauncher::ShootWeapon(float xPos, float yPos)
{
	if (mFiringTimer > mRateOfFire)
	{
		mFiringTimer = 0.0f;
		CreateRocket(xPos, yPos);
	}
}

//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------

void CRocketLauncher::CreateRocket(float xPos, float yPos)
{
	// If we have bullets already made and in reserve, move a bullet from the reserse to the active list
	if (mResetRockets.size() != 0)
	{
		mResetRockets.back()->SetFromEnemy(IsEnemyWeapon());
		mResetRockets.back()->SetSpeed(mSpeed);
		mResetRockets.back()->SetLifetime(mLifetime);
		mResetRockets.back()->GetModel()->SetPosition(xPos, yPos, 0.0f);
		mAmmoList.push_front(move(mResetRockets.back()));
		mResetRockets.pop_back();
	}
	else
		// Create a new bullet from scratch
		mAmmoList.push_front(std::make_unique<CRocket>(GetResources(), mLifetime, mSpeed, xPos, yPos, IsEnemyWeapon()));
}