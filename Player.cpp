//project inlcude
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Level.h"

Player::Player()
	: GridObject()
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
}

void Player::Input(sf::Event _GameEvent)
{
	//read the input from the keyboard
	//convert it to a direction to move in
	//the move

	//was the _GameEvent a keypress?
	if (_GameEvent.type == sf::Event::KeyPressed)
	{
		//yes, it was a keypress

		//what key was pressed?
		if (_GameEvent.key.code == sf::Keyboard::W || _GameEvent.key.code == sf::Keyboard::Up)
		{
			// it was W that was pressed
			//move up
			AttemptMove(sf::Vector2i(0, -1));
		}
		else if (_GameEvent.key.code == sf::Keyboard::A || _GameEvent.key.code == sf::Keyboard::Left)
		{
			// it was A that was pressed
			//move left
			AttemptMove(sf::Vector2i(-1, 0));
		}
		else if (_GameEvent.key.code == sf::Keyboard::S || _GameEvent.key.code == sf::Keyboard::Down)
		{
			// it was S that was pressed
			//move down
			AttemptMove(sf::Vector2i(0, 1));
		}
		else if (_GameEvent.key.code == sf::Keyboard::D || _GameEvent.key.code == sf::Keyboard::Right)
		{
			// it was D that was pressed
			//move Right
			AttemptMove(sf::Vector2i(1, 0));
		}
	}
}

bool Player::AttemptMove(sf::Vector2i _Direction)
{
	// Attempt to move in the given direction

	//get the current position
	//calculatye the target position
	sf::Vector2i TargetPos = m_GridPosition + _Direction;

	// TODO: check if the space is empty

	//if empty, move there
	return m_Level->MoveObjectTo(this, TargetPos);
}