//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "LaserGun.h"

#include "LaserBeam.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CLaserGun::CLaserGun(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
	std::list<std::unique_ptr<CAmmo>>& resetBeams, bool enemyShooting) :
	CWeapon(pResources, enemyShooting), mAmmoList{ ammoList }, mResetBeams{ resetBeams }
{
}


CLaserGun::~CLaserGun()
{
}

void CLaserGun::ShootWeapon(float xPos, float yPos)
{
	CreateBeam(xPos, yPos);
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------

void CLaserGun::CreateBeam(float xPos, float yPos, float distance, float angle)
{
	// If we have bullets already made and in reserve, move a bullet from the reserse to the active list
	if (mResetBeams.size() != 0)
	{
		mResetBeams.back()->GetModel()->ResetOrientation();
		mResetBeams.back()->GetModel()->ResetScale();

		if (mResetBeams.back()->FromEnemy() != IsEnemyWeapon())
		{
			mResetBeams.back()->SetFromEnemy(IsEnemyWeapon());
			mResetBeams.back()->GetBeam()->DetachFromParent();
			mResetBeams.back()->GetModel()->SetPosition(0.0f, 0.0f, 0.0f);

			if (IsEnemyWeapon())
				mResetBeams.back()->GetBeam()->SetPosition(distance * -LASER_X_OFFSET, 0.0f, 0.0f);
			else
				mResetBeams.back()->GetBeam()->SetPosition(distance * LASER_X_OFFSET, 0.0f, 0.0f);

			mResetBeams.back()->GetBeam()->AttachToParent(mResetBeams.back()->GetModel());
		}
	
		mResetBeams.back()->GetModel()->SetPosition(xPos, yPos, LASER_Z);
		mResetBeams.back()->GetModel()->ScaleX(distance * 0.5f);
		mResetBeams.back()->GetModel()->RotateZ(angle);
		mAmmoList.push_front(move(mResetBeams.back()));
		mResetBeams.pop_back();
	}
	else
		// Create a new bullet from scratch
		mAmmoList.push_front(std::make_unique<CLaserBeam>(GetResources(), distance, angle, xPos, yPos, IsEnemyWeapon()));
}