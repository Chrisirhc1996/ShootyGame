#pragma once

// Dependencies
#include <TL-Engine.h>	// TL-Engine include file and namespace

class CResourceManager
{
private:
	// Variables //
	tle::I3DEngine* mpMyEngine;
	tle::ICamera* mpMyCamera;

	tle::IMesh* mpPlayerMesh;			// The players ship
	tle::IMesh* mpParticleMesh;			// Flare effects
	tle::IMesh* mpQuadMesh;				// For buttons, bullets etc


public:
	CResourceManager();
	~CResourceManager();

	void LoadResources();

	tle::I3DEngine* GetEngine() { return mpMyEngine; }
	tle::ICamera* GetCamera() { return mpMyCamera; }
	tle::IMesh* GetPlayerMesh() { return mpPlayerMesh; }
	tle::IMesh* GetParticleMesh() { return mpParticleMesh; }
	tle::IMesh* GetQuadMesh() { return mpQuadMesh; }
};


//// Singleton class
//class CResourceManager
//{
//private:
//	static bool instanceFlag;
//	static CResourceManager* single;
//
//	// Private constructor
//	CResourceManager();
//
//	// Variables //
//	tle::I3DEngine* mpMyEngine;
//	tle::ICamera* mpMyCamera;
//
//	tle::IMesh* mpPlayerMesh;			// The players ship
//	tle::IMesh* mpParticleMesh;			// For bullets, buttons etc
//
//
//public:
//	static CResourceManager* getInstance();
//
//	void LoadResources();
//
//	tle::I3DEngine* GetEngine() { return mpMyEngine; }
//	tle::IMesh* GetPlayerMesh() { return mpPlayerMesh; }
//	tle::IMesh* GetParticleMesh() { return mpParticleMesh; }
//
//	~CResourceManager();
//};