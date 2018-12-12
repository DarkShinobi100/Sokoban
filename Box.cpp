//project inlcude
#include "Box.h"
#include "Framework/AssetManager.h"
#include "Level.h"

Box::Box()
	: GridObject()
	, m_PushSound()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
	m_BlocksMovement = true;
	m_PushSound.setBuffer(AssetManager::GetSoundBuffer("audio/push.wav"));
}

bool Box::AttemptPush(sf::Vector2i _direction)
{
	//attempt to move the box in the given direction

	//get the current position
	//calculate the target position
	sf::Vector2i TargetPos = m_GridPosition + _direction;

	// check if the space is empty
	// get list of  objects in our target position
	std::vector<GridObject*> TargetCellContents = m_Level->GetObjectAt(TargetPos);

	// check if any of those objects block movement
	bool blocked = false;
	for (int i = 0; i < TargetCellContents.size(); ++i)
	{
		if (TargetCellContents[i]->GetBlockedMovement() == true)
		{
			blocked = true;
		}
	}

	//if empty, move there
	if (blocked == false)
	{
		m_PushSound.play();
		return m_Level->MoveObjectTo(this, TargetPos);
	}
	//if movement is blocked, do nothing, return false
	return false;
}