#pragma once

//project includes
#include "Framework/SpriteObject.h"

//Forward Declaration
//only works with pointers(*)/references(&)
class Level;

class GridObject : public SpriteObject
{

public:

	GridObject();

	void SetGridPosition(sf::Vector2i _NewPosition);

	//overloaded function
	void SetGridPosition(int _x,int _y);

	void SetLevel(Level* _NewLevel);

private:

	sf::Vector2i m_GridPosition;
	Level* m_Level;


};