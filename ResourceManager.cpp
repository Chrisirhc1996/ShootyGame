//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "ResourceManager.h"
#include "Globals.h"

//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CResourceManager::CResourceManager()
{
	// Create a 3D engine
	mpMyEngine = tle::New3DEngine(tle::kTLX);

	if (!mpMyEngine)
		throw;
}

// Destructor
CResourceManager::~CResourceManager()
{
	// Remove meshes
	mpMyEngine->RemoveMesh(mpParticleMesh);
	mpMyEngine->RemoveMesh(mpPlayerMesh);

	// Delete the 3D engine now we are finished with it
	mpMyEngine->Delete();
	mpMyEngine = nullptr;
}

void CResourceManager::LoadResources()
{
	// Create the main default camera
	mpMyCamera = mpMyEngine->CreateCamera(tle::kManual, 0.0f, 0.0f, CAMERA_Z);

	// Load meshes
	mpPlayerMesh = mpMyEngine->LoadMesh(SPACESHIP_MESH);
	mpParticleMesh = mpMyEngine->LoadMesh(PARTICLE_MESH);
	mpQuadMesh = mpMyEngine->LoadMesh(QUAD_MESH);
}


// Singleton implimentation //

////-----------------------------------------------------------------------------
////---- Private static variables -----------------------------------------------
////-----------------------------------------------------------------------------
//
//bool CResourceManager::instanceFlag = false;
//CResourceManager* CResourceManager::single = nullptr;
//
////-----------------------------------------------------------------------------
////---- Private Methods --------------------------------------------------------
////-----------------------------------------------------------------------------
//
//// Private constructor
//CResourceManager::CResourceManager()
//{
//	// Create a 3D engine
//	mpMyEngine = tle::New3DEngine(tle::kTLX);
//
//	if (!mpMyEngine)
//	throw;
//}
//
//
////-----------------------------------------------------------------------------
////---- Public Methods ---------------------------------------------------------
////-----------------------------------------------------------------------------
//
//// Static method for creating or getting an instance
//CResourceManager* CResourceManager::getInstance()
//{
//	if (!instanceFlag)
//	{
//		single = new CResourceManager();
//		instanceFlag = true;
//		return single;
//	}
//	else
//	{
//		return single;
//	}
//}
//
//void CResourceManager::LoadResources()
//{
//
//	// Create the main default camera
//	mpMyCamera = mpMyEngine->CreateCamera(tle::kManual, 0.0f, 0.0f, CAMERA_Z);
//
//	// Load meshes
//	mpPlayerMesh = mpMyEngine->LoadMesh(SPACESHIP_MESH);
//	mpParticleMesh = mpMyEngine->LoadMesh(BULLET_MESH);
//}
//
//// Destructor
//CResourceManager::~CResourceManager()
//{
//	instanceFlag = false;
//
//	// Remove meshes
//	mpMyEngine->RemoveMesh(mpParticleMesh);
//	mpMyEngine->RemoveMesh(mpPlayerMesh);
//
//	// Delete the 3D engine now we are finished with it
//	mpMyEngine->Delete();
//	mpMyEngine = nullptr;
//}
