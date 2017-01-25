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
	// Create UI
	mpUIBorder = mpResources->GetQuadMesh()->CreateModel(-4.0f, 0.0f, -95.0f);
	mpUIBorder->RotateX(180.0f);
	mpUIBorder->SetSkin(BORDER);
	mpUIBorder2 = mpResources->GetQuadMesh()->CreateModel(4.0f, 0.0f, -95.0f);
	mpUIBorder2->RotateY(180.0f);
	mpUIBorder2->SetSkin(BORDER);

	// Create player
	mpPlayer = std::make_unique<CPlayer>(mpResources);
	
}


CLevel::~CLevel()
{
	// Cleanup sprites
	mpResources->GetQuadMesh()->RemoveModel(mpUIBorder);
	mpResources->GetQuadMesh()->RemoveModel(mpUIBorder2);
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