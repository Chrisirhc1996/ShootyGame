#include "GameManager.h"
#include <memory>


void main()
{
	std::unique_ptr<CGameManager> pGame = std::make_unique<CGameManager>();

	pGame->RunGame();
}