// BulletTest.cpp: A program using the TL-Engine

#include <TL-Engine.h>  // TL-Engine include file and namespace
#include <deque>
#include "weapon.h"
#include "bullet.h"

using namespace tle;

const float BULLET_SPEED = 30.0f;
const float BULLET_LIFETIME = 1000.0f;
const float BULLET_RADIUS = 1.0f;

const float PLAYER_POS_X = 0.0f;
const float PLAYER_POS_Y = 0.0f;
const float PLAYER_POS_Z = 80.0f;

const string PARTICLE_MESH = "bullet.x";
const string PARTICLE_MODEL = "010_tlxadd.tga";


void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");

	bool isExpired = false;
	float mFrameTime;
	deque <CBullets> currentBullets;
	CBullets* bulletPointer;
	/**** Set up your scene here ****/

	// Cbbe to emit particles from
	IMesh* emitterMesh = myEngine->LoadMesh("Cube.x");
	IModel* emitter = emitterMesh->CreateModel(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);

	IMesh* particleMesh = myEngine->LoadMesh(PARTICLE_MESH);

	ICamera* myCamera = myEngine->CreateCamera(kManual);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();
		mFrameTime = myEngine->Timer();

		/**** Update your scene each frame here ****/

		// Removes particle from play when duration expires
		if (isExpired)
		{
			currentBullets.pop_back();

		}

		// Creates a new particle from the emitter
 		if (myEngine->KeyHit(Key_Space))
		{
			bulletPointer = new CBullets(myEngine, particleMesh, "particle", BULLET_LIFETIME, BULLET_SPEED, BULLET_RADIUS);
			bulletPointer->SetLifetime(BULLET_LIFETIME);
			bulletPointer->SetSpeed(BULLET_SPEED);
			bulletPointer->SetRadius(BULLET_RADIUS);
			currentBullets.push_front(*bulletPointer);
		}

		// Prevents trying to examine an empty deque
		if (!currentBullets.empty())
		{
			currentBullets.back().GetLifetime();
		}

		// Decreases the lifetime on each particle in play and moves it accordingly
		for (auto it = currentBullets.begin(); it != currentBullets.end(); ++it)
		{
			(*it).MoveBullet(mFrameTime);
			if ((*it).GetLifetime() <= 0.0f)
			{
				isExpired;
			}
		}

		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
			myEngine->StopMouseCapture();
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
