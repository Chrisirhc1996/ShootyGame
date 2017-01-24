//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Bullets.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

//////////////////////BULLET.CPP

CBullets::CBullets(tle::I3DEngine* mpMyEngine, tle::IMesh* mMesh, string type, float mLifetime, float mSpeed, float mRadius)
{
	if (type == "particle")
	{
		mModel = mMesh->CreateModel(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);
		mLifetime = BULLET_LIFETIME;
		mSpeed = BULLET_SPEED;
		mRadius = BULLET_RADIUS;
	}
}


CBullets::~CBullets()
{
}

void CBullets::MoveBullet(float frameTime)
{
	mModel->MoveX(mSpeed * frameTime);
	mLifetime -= frameTime;


}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------
