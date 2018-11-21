#pragma once

//library includes
#include <SFML/Graphics.hpp>
class Level
{

public:
	Level();

	void Draw(sf::RenderTarget& _Target);
	void Update(sf::Time _FrameTime);

	void LoadLevel(int _LevelToLoad);
	void ReloadLevel();
	void LoadNextLevel();

private:

	const float m_CellSize;
	int m_CurrentLevel;
	std::vector< std::vector < sf::Sprite > > m_Background;

};