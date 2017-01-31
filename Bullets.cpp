#include "Bullets.h"



CBullets::CBullets(tle::IMesh* pBulletMesh, float lifetime, float speed, float xPos, float yPos) :
	mLifeLeft{ lifetime }, mSpeed{ speed }
{

}


CBullets::~CBullets()
{
}
