//project inlcude
#include "Player.h"
#include "Framework/AssetManager.h"

Player::Player()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
}