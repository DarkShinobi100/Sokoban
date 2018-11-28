#pragma once

//project includes
#include "GridObject.h"

class Player : public GridObject
{

public:
	Player();

	//Overriding methods
	void Input(sf::Event _GameEvent);


private:

	bool AttemptMove(sf::Vector2i _Direction);

};