//project inlcude
#include "StorageObject.h"
#include "Framework/AssetManager.h"

StorageObject::StorageObject()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/storage.png"));
}