//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Level.h"
#include "Globals.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CLevel::CLevel(CResourceManager* pResources) :
	mpResources{ pResources }
{
	// Create sprites
	mpUIBorder = mpResources->GetEngine()->CreateSprite(BORDER, 0.0f, 0.0f, 1.0f);

	// Create player
	mpPlayer = std::make_unique<CPlayer>(mpResources);
	
}


CLevel::~CLevel()
{
	// Cleanup models
	mpResources->GetPlayerMesh()->RemoveModel(mpPlayer->GetModel());

	// Cleanup sprites
	mpResources->GetEngine()->RemoveSprite(mpUIBorder);
}

// Play the current level
void CLevel::PlayLevel(float frameTime)
{
	mpPlayer->MovePlayer(frameTime);

	if (mpResources->GetEngine()->KeyHeld(tle::Key_Space))
	{
		mpPlayer->GetWeaponSystem()->ShootWeapon(mpPlayer->GetXPos(), mpPlayer->GetYPos());
	}

	mpPlayer->GetWeaponSystem()->MoveWeaponParticles(frameTime);
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------