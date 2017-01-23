//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Level.h"
#include "Globals.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CLevel::CLevel(tle::I3DEngine* pMyEngine, tle::IMesh* pPlayerMesh) :
	mpMyEngine{ pMyEngine }, mpPlayerMesh{ pPlayerMesh }
{
	mpPlayer = std::make_unique<CPlayer>(pMyEngine, pPlayerMesh, -60.0f, 0.0f);
	mpUIBorder = mpMyEngine->CreateSprite(BORDER, 0.0f, 0.0f);
}


CLevel::~CLevel()
{
	// Cleanup models
	mpPlayerMesh->RemoveModel(mpPlayer->GetModel());

	// Cleanup sprites
	mpMyEngine->RemoveSprite(mpUIBorder);
}

// Play the current level
void CLevel::PlayLevel(float frameTime)
{
	mpPlayer->MovePlayer(frameTime);
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------