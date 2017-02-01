//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Ammo.h"
#include "ResourceManager.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CAmmo::CAmmo(CResourceManager* pResources, bool isEnemyWeapon, float lifetime) :
	mpResources{ pResources }, mFromEnemyWeapon{ isEnemyWeapon }, mLifetimeLeft{ lifetime }
{
}


CAmmo::~CAmmo()
{
}
