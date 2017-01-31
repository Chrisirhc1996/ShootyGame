//-----------------------------------------------------------------------------
//---- Dependencies -----------------------------------------------------------
//-----------------------------------------------------------------------------

#include "Entity.h"


//-----------------------------------------------------------------------------
//---- Public Methods ---------------------------------------------------------
//-----------------------------------------------------------------------------

CEntity::CEntity(CResourceManager* pResources) :
	mpResources{ pResources }
{
}

CEntity::~CEntity()
{
	// Cleanup models
	mpResources->GetPlayerMesh()->RemoveModel(mpModel);
}
