//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Level.h"
#include "Globals.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------


CLevel::CLevel(tle::I3DEngine* pMyEngine) :
	mpMyEngine{ pMyEngine }
{
	// Load meshes
	mpPlayerMesh = mpMyEngine->LoadMesh(SPACESHIP_MESH);
	mpParticleMesh = mpMyEngine->LoadMesh(BULLET_MESH);

	// Create sprites
	mpUIBorder = mpMyEngine->CreateSprite(BORDER, 0.0f, 0.0f, 1.0f);

	// Create player
	mpPlayer = std::make_unique<CPlayer>(pMyEngine, mpPlayerMesh, mpParticleMesh);
	
}


CLevel::~CLevel()
{
	// Cleanup models
	mpPlayerMesh->RemoveModel(mpPlayer->GetModel());

	// Cleanup sprites
	mpMyEngine->RemoveSprite(mpUIBorder);

	// Cleanup the meshes
	mpMyEngine->RemoveMesh(mpPlayerMesh);
	mpPlayerMesh = nullptr;
}

// Play the current level
void CLevel::PlayLevel(float frameTime)
{
	mpPlayer->MovePlayer(frameTime);

	if (mpMyEngine->KeyHeld(tle::Key_Space))
	{
		mpPlayer->GetWeaponSystem()->ShootWeapon(mpPlayer->GetXPos(), mpPlayer->GetYPos());
	}

	mpPlayer->GetWeaponSystem()->MoveWeaponParticles(frameTime);
}


//-----------------------------------------------------------------------------
//---- Private Methods --------------------------------------------------------
//-----------------------------------------------------------------------------