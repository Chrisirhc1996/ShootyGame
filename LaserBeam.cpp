//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "LaserBeam.h"

#include "ResourceManager.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CLaserBeam::CLaserBeam(CResourceManager* pResources, float distance, float angle, float xPos, float yPos, bool isEnemyWeapon) :
	CAmmo(pResources, isEnemyWeapon, 0.0f /*duration*/), mDistance{ distance }
{
	SetAmmoType(LASERS);

	// We make the normally accessed model the dummy object as this is where we control movement and 
	// rotation from and set a new model up in this class for the beam model

	SetModel(pResources->GetDummyMesh()->CreateModel());

	if (isEnemyWeapon)
		mpBeam = pResources->GetQuadMesh()->CreateModel(distance * -LASER_X_OFFSET);
	else
		mpBeam = pResources->GetQuadMesh()->CreateModel(distance * LASER_X_OFFSET);
	mpBeam->SetSkin(LASER_SPRITE);
	mpBeam->ScaleY(0.08f);
	mpBeam->AttachToParent(GetModel());
	GetModel()->SetPosition(xPos, yPos, LASER_Z);
	GetModel()->ScaleX(distance * 0.5f);
	GetModel()->RotateZ(angle);
}


CLaserBeam::~CLaserBeam()
{
}

bool CLaserBeam::Move(float frameTime)
{
	SetLifetime(GetLifeTimeRemaining() - frameTime);

	if (GetLifeTimeRemaining() <= 0.0f)
	{
		GetModel()->MoveY(1000.0f);
		return true;
	}
	return false;
}
