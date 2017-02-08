//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "PlasmaShot.h"

#include "ResourceManager.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPlasmaShot::CPlasmaShot(CResourceManager* pResources, float lifetime, float speed, float xPos, float yPos, bool isEnemyWeapon) :
	CAmmo(pResources, isEnemyWeapon, lifetime), mSpeed{ speed }
{
	SetModel(GetResources()->GetQuadMesh()->CreateModel(xPos, yPos));
	GetModel()->SetSkin(PLASMA_SPRITE);
	GetModel()->Scale(0.5f);
}

CPlasmaShot::~CPlasmaShot()
{
}


bool CPlasmaShot::Move(float frameTime)
{
	GetModel()->MoveX(mSpeed * frameTime);
	SetLifetime(GetLifeTimeRemaining() - frameTime);

	if (GetLifeTimeRemaining() <= 0.0f)
	{
		GetModel()->MoveY(800.0f);
		return true;
	}
	return false;
}