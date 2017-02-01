#pragma once

// Dependencies
#include "Entity.h"

#include <TL-Engine.h>
#include <memory>
#include <list>

class CResourceManager;
class CAmmo;


class CEnemy : public CEntity
{
private:
	// Variables //

public:
	// Constructor
	CEnemy(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
		std::list<std::unique_ptr<CAmmo>>& resetList);
	//  Destructor
	virtual ~CEnemy();

private:
	// Private Methods //
};

