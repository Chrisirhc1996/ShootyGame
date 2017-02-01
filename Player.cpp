//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Player.h"

#include "Globals.h"
#include "ResourceManager.h"
#include "Weapon.h"
#include "Blaster.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPlayer::CPlayer(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList) :
	CEntity{ pResources }
{
	SetModel(GetResources()->GetPlayerMesh()->CreateModel(PLAYER_START_X, PLAYER_START_Y));
	GetModel()->RotateY(90.0f);
	std::unique_ptr<CWeapon> weapon = std::make_unique<CBlaster>(GetResources(), ammoList, false);
	SetWeaponSystem(weapon);
}

CPlayer::~CPlayer()
{
}

// Movement within a restricted area (up, down, left or right)
void CPlayer::Move(float frameTime)
{
	// Move up or down
	if (GetResources()->GetEngine()->KeyHeld(UP))
	{
		if (GetYPos() < PLAYER_MAX_Y)
			GetModel()->MoveY(PLAYER_SPEED * frameTime);
	}
	else if (GetResources()->GetEngine()->KeyHeld(DOWN))
	{
		if (GetYPos() > PLAYER_MIN_Y)
			GetModel()->MoveY(-PLAYER_SPEED * frameTime);
	}

	// Move left or right
	if (GetResources()->GetEngine()->KeyHeld(LEFT))
	{
		if (GetXPos() > PLAYER_MIN_X)
			GetModel()->MoveX(-PLAYER_SPEED * frameTime);
	}
	else if (GetResources()->GetEngine()->KeyHeld(RIGHT))
	{
		if (GetXPos() < PLAYER_MAX_X)
			GetModel()->MoveX(PLAYER_SPEED * frameTime);
	}
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------
