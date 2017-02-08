//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Rocket.h"

#include "ResourceManager.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CRocket::CRocket(CResourceManager* pResources, float lifetime, float speed, float xPos, float yPos, bool isEnemyWeapon) :
	CAmmo(pResources, isEnemyWeapon, lifetime), mSpeed{ speed }
{
	SetModel(GetResources()->GetQuadMesh()->CreateModel(xPos, yPos));
	GetModel()->SetSkin(ROCKET_SPRITE);
	GetModel()->Scale(0.5f);
}

CRocket::~CRocket()
{
}


bool CRocket::Move(float frameTime)
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