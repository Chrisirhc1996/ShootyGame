//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Bullets.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CBullets::CBullets(tle::IMesh* pBulletMesh) :
	CWeapon(pBulletMesh)
{
	mLifetime = 4.0f;
	mSpeed = 60.0f;
	mRateOfFire = 0.2f;
}


CBullets::~CBullets()
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

void CBullets::MoveWeaponParticles(float frameTime)
{
	bool bulletExpired = false;
	for (auto& bullet : bullets)
	{
		bullet->mpBulletModel->MoveX(mSpeed * frameTime);
		bullet->mLifeLeft -= frameTime;

		if (bullet->mLifeLeft <= 0.0f)
		{
			bulletExpired = true;
			resetBullets.push_back(move(bullet));
		}
	}
	if (bulletExpired)
		bullets.pop_back();

	mFiringTimer += frameTime;
}

void CBullets::ShootWeapon(float xPos, float yPos)
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

void CBullets::CreateBullet(float xPos, float yPos)
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











////////////////////////BULLET.CPP
//
//CBullets::CBullets(tle::I3DEngine* mpMyEngine, tle::IMesh* mMesh, string type, float mLifetime, float mSpeed, float mRadius)
//{
//	if (type == "particle")
//	{
//		mModel = mMesh->CreateModel(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);
//		mLifetime = BULLET_LIFETIME;
//		mSpeed = BULLET_SPEED;
//		mRadius = BULLET_RADIUS;
//	}
//}
//
//
//CBullets::~CBullets()
//{
//}
//
//void CBullets::MoveBullet(float frameTime)
//{
//	mModel->MoveX(mSpeed * frameTime);
//	mLifetime -= frameTime;
//}