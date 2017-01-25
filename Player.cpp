//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Player.h"
#include "Blaster.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPlayer::CPlayer(CResourceManager* pResources) :
	mpResources{ pResources }
{
	mpPlayerModel = mpResources->GetPlayerMesh()->CreateModel(PLAYER_START_X, PLAYER_START_Y);
	mpPlayerModel->RotateY(90.0f);

	mpWeaponSystem = std::make_unique<CBlaster>(mpResources);
}

CPlayer::~CPlayer()
{
}

// Movement within a restricted area (up, down, left or right)
void CPlayer::MovePlayer(float frameTime)
{
	// Move up or down
	if (mpResources->GetEngine()->KeyHeld(UP))
	{
		if (mpPlayerModel->GetY() < PLAYER_MAX_Y)
			mpPlayerModel->MoveY(PLAYER_SPEED * frameTime);
	}
	else if (mpResources->GetEngine()->KeyHeld(DOWN))
	{
		if (mpPlayerModel->GetY() > PLAYER_MIN_Y)
			mpPlayerModel->MoveY(-PLAYER_SPEED * frameTime);
	}

	// Move left or right
	if (mpResources->GetEngine()->KeyHeld(LEFT))
	{
		if (mpPlayerModel->GetX() > PLAYER_MIN_X)
			mpPlayerModel->MoveX(-PLAYER_SPEED * frameTime);
	}
	else if (mpResources->GetEngine()->KeyHeld(RIGHT))
	{
		if (mpPlayerModel->GetX() < PLAYER_MAX_X)
			mpPlayerModel->MoveX(PLAYER_SPEED * frameTime);
	}
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------
