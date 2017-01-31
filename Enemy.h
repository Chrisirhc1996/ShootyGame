#pragma once

// Dependencies
#include "Entity.h"

#include <TL-Engine.h>
#include <memory>

class CResourceManager;


class CEnemy : public CEntity
{
private:
	// Variables //

public:
	// Constructor
	CEnemy(CResourceManager* pResources);
	//  Destructor
	virtual ~CEnemy();

private:
	// Private Methods //
};

