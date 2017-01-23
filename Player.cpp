//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Player.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CPlayer::CPlayer(tle::I3DEngine* pMyEngine, tle::IMesh* pPlayerMesh, float xPos, float yPos) :
	mpMyEngine{ pMyEngine }, mXPos{ xPos }, mYPos{ yPos }
{
	mpPlayerModel = pPlayerMesh->CreateModel(xPos, yPos);
	mpPlayerModel->RotateY(90.0f);
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
