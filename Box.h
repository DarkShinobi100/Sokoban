#pragma once

//project includes
#include "GridObject.h"

class Box : public GridObject
{

public:
	Box();

	bool AttemptPush(sf::Vector2i _direction);

private:

	bool m_Stored;
	sf::Sound m_PushSound;
	sf::Sound m_StoredSound;
};