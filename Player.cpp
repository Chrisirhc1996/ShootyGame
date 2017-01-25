//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Player.h"
#include "Bullets.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPlayer::CPlayer(tle::I3DEngine* pMyEngine, tle::IMesh* pPlayerMesh, tle::IMesh* pParticleMesh) :
	mpMyEngine{ pMyEngine }, mpParticleMesh{ pParticleMesh }
{
	mpPlayerModel = pPlayerMesh->CreateModel(PLAYER_START_X, PLAYER_START_Y);
	mpPlayerModel->RotateY(90.0f);

	mpWeaponSystem = std::make_unique<CBullets>(mpParticleMesh);
}

CPlayer::~CPlayer()
{
}

// Movement within a restricted area (up, down, left or right)
void CPlayer::MovePlayer(float frameTime)
{
	// Move up or down
	if (mpMyEngine->KeyHeld(UP))
	{
		if (mpPlayerModel->GetY() < PLAYER_MAX_Y)
			mpPlayerModel->MoveY(PLAYER_SPEED * frameTime);
	}
	else if (mpMyEngine->KeyHeld(DOWN))
	{
		if (mpPlayerModel->GetY() > PLAYER_MIN_Y)
			mpPlayerModel->MoveY(-PLAYER_SPEED * frameTime);
	}

	// Move left or right
	if (mpMyEngine->KeyHeld(LEFT))
	{
		if (mpPlayerModel->GetX() > PLAYER_MIN_X)
			mpPlayerModel->MoveX(-PLAYER_SPEED * frameTime);
	}
	else if (mpMyEngine->KeyHeld(RIGHT))
	{
		if (mpPlayerModel->GetX() < PLAYER_MAX_X)
			mpPlayerModel->MoveX(PLAYER_SPEED * frameTime);
	}
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------
