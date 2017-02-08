//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "PlasmaCannon.h"

#include "PlasmaShot.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPlasmaCannon::CPlasmaCannon(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
	std::list<std::unique_ptr<CAmmo>>& resetPlasma, bool enemyShooting) :
	CWeapon(pResources, enemyShooting), mAmmoList{ ammoList }, mResetPlasma{ resetPlasma }
{
	mLifetime = 4.0f;
	mRateOfFire = 2.0f;
	if (enemyShooting)
		mSpeed = -20.0f;
	else
		mSpeed = 20.0f;
}


CPlasmaCannon::~CPlasmaCannon()
{
}



void CPlasmaCannon::ShootWeapon(float xPos, float yPos)
{
	if (mFiringTimer > mRateOfFire)
	{
		mFiringTimer = 0.0f;
		CreatePlasma(xPos, yPos);
	}
}

//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------

void CPlasmaCannon::CreatePlasma(float xPos, float yPos)
{
	// If we have bullets already made and in reserve, move a bullet from the reserse to the active list
	if (mResetPlasma.size() != 0)
	{
		mResetPlasma.back()->SetFromEnemy(IsEnemyWeapon());
		mResetPlasma.back()->SetSpeed(mSpeed);
		mResetPlasma.back()->SetLifetime(mLifetime);
		mResetPlasma.back()->GetModel()->SetPosition(xPos, yPos, 0.0f);
		mAmmoList.push_front(move(mResetPlasma.back()));
		mResetPlasma.pop_back();
	}
	else
		// Create a new bullet from scratch
		mAmmoList.push_front(std::make_unique<CPlasmaShot>(GetResources(), mLifetime, mSpeed, xPos, yPos, IsEnemyWeapon()));
}