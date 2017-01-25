//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Blaster.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CBlaster::CBlaster(tle::IMesh* pBulletMesh) :
	CWeapon(pBulletMesh)
{
	mLifetime = 4.0f;
	mSpeed = 60.0f;
	mRateOfFire = 0.2f;
}


CBlaster::~CBlaster()
{
	// Clean up models
	for (auto& bullet : bullets)
	{
		GetWeaponMesh()->RemoveModel(bullet->mpBulletModel);
	}
	for (auto& bullet : resetBullets)
	{
		GetWeaponMesh()->RemoveModel(bullet->mpBulletModel);
	}
}

void CBlaster::MoveWeaponParticles(float frameTime)
{
	bool bulletExpired = false;
	for (auto& bullet : bullets)
	{
		bullet->mpBulletModel->MoveX(mSpeed * frameTime);
		bullet->mLifeLeft -= frameTime;

		if (bullet->mLifeLeft <= 0.0f)
		{
			bullet->mpBulletModel->MoveY(1000.0f);
			bulletExpired = true;
			resetBullets.push_back(move(bullet));
		}
	}
	if (bulletExpired)
		bullets.pop_back();

	mFiringTimer += frameTime;
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
	if (resetBullets.size() != 0)
	{
		resetBullets.back()->mLifeLeft = mLifetime;
		resetBullets.back()->mpBulletModel->SetPosition(xPos, yPos, 0.0f);
		bullets.push_front(move(resetBullets.back()));
		resetBullets.pop_back();
	}
	else
		bullets.push_front(std::make_unique<SBullet>(GetWeaponMesh(), mLifetime, mSpeed, xPos, yPos));
}