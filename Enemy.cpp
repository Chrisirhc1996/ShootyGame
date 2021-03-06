//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Enemy.h"

#include "Globals.h"
#include "ResourceManager.h"
#include "Weapon.h"
#include "Blaster.h"
#include "LaserGun.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CEnemy::CEnemy(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
	std::list<std::unique_ptr<CAmmo>>& resetList) :
	CEntity{ pResources }
{
	SetModel(GetResources()->GetPlayerMesh()->CreateModel(PLAYER_START_X + 100.0f, PLAYER_START_Y));
	GetModel()->RotateY(-90.0f);
	std::unique_ptr<CWeapon> weapon = std::make_unique<CLaserGun>(GetResources(), ammoList, resetList);
	SetWeaponSystem(weapon);
}


CEnemy::~CEnemy()
{
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------