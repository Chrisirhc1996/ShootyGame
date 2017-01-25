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
	tle::IMesh* mpParticleMesh;			// For bullets, buttons etc


public:
	CResourceManager();
	~CResourceManager();

	void LoadResources();

	tle::I3DEngine* GetEngine() { return mpMyEngine; }
	tle::IMesh* GetPlayerMesh() { return mpPlayerMesh; }
	tle::IMesh* GetParticleMesh() { return mpParticleMesh; }	
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