//project inlcude
#include "Box.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "StorageObject.h"

Box::Box()
	: GridObject()
	, m_Stored(false)
	, m_PushSound()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
	m_BlocksMovement = true;
	m_PushSound.setBuffer(AssetManager::GetSoundBuffer("audio/push.wav"));
	m_StoredSound.setBuffer(AssetManager::GetSoundBuffer("audio/stored.wav"));
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
		bool moveSucceeded =  m_Level->MoveObjectTo(this, TargetPos);

		//if we did successfull move...
		if (moveSucceeded == true)
		{
			//check if we are stored

			//assume we are mot stored to start
			m_Stored = false;

			//loop through the contents and see if a storage object was found
			for (int i = 0; i < TargetCellContents.size(); ++i)
			{
				//check if this element in the vector is a storage object
				//by doing a dynamic cast
				StorageObject* storageSpace = dynamic_cast<StorageObject*>(TargetCellContents[i]);
				//if dynamic cast succeeds, it will NOT be a nullptr
				//aka, the object is a storage object.
				if (storageSpace != nullptr)
				{
					//the object is a storage object

					//we are stored
					m_Stored = true;
				}
			}

			//change our sprite accordingly
			if (m_Stored)
			{
				//change sprite
				m_Sprite.setTexture(AssetManager::GetTexture("graphics/boxStored.png"));
				m_StoredSound.play();
				
				//check if the level is complete
				m_Level->CheckComplete();
			}
			else
			{
				//change sprite back
				m_Sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
			}
		}

		return moveSucceeded;
	}
	//if movement is blocked, do nothing, return false
	return false;
}

bool Box::GetStored()
{
	return m_Stored;
}