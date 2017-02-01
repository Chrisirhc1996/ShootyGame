//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Bullet.h"

#include "ResourceManager.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CBullet::CBullet(CResourceManager* pResources, float lifetime, float speed, float xPos, float yPos, bool isEnemyWeapon) :
	CAmmo(pResources, isEnemyWeapon, lifetime), mSpeed{ speed }
{
	SetModel(GetResources()->GetQuadMesh()->CreateModel(xPos, yPos));
	GetModel()->SetSkin(BULLET_SPRITE);
	GetModel()->Scale(0.1f);
}

CBullet::~CBullet()
{
}


bool CBullet::Move(float frameTime)
{
	GetModel()->MoveX(mSpeed * frameTime);
	SetLifetime(GetLifeTimeRemaining() - frameTime);

	if (GetLifeTimeRemaining() <= 0.0f)
	{
		GetModel()->MoveY(1000.0f);
		return true;
	}
	return false;
}