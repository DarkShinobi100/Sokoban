//project inlcude
#include "Box.h"
#include "Framework/AssetManager.h"

Box::Box()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
	m_BlocksMovement = true;
}