//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Enemy.h"

#include "Globals.h"
#include "ResourceManager.h"
#include "Weapon.h"
#include "Blaster.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CEnemy::CEnemy(CResourceManager* pResources) :
	CEntity{ pResources }
{
	SetModel(GetResources()->GetPlayerMesh()->CreateModel(PLAYER_START_X + 100.0f, PLAYER_START_Y));
	GetModel()->RotateY(-90.0f);
	std::unique_ptr<CWeapon> weapon = std::make_unique<CBlaster>(GetResources());
	SetWeaponSystem(weapon);
}


CEnemy::~CEnemy()
{
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------