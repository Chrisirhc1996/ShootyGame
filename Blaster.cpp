//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Blaster.h"
#include "Enemy.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CBlaster::CBlaster(CResourceManager* pResources, bool enemyShooting) :
	CWeapon(pResources, enemyShooting)
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

bool CBlaster::CollisionCheck(CEnemy* enemy)
{
	for (auto& bullet : bullets)
	{
		if (fabs(bullet->mpBulletModel->GetX() - enemy->GetXPos()) < 5.0f/*half model length*/ &&
			fabs(bullet->mpBulletModel->GetY() - enemy->GetYPos()) < 2.0f/*half model height*/)
		{
			// Theres been a collision!
			return true;
		}
	}
	return false;
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