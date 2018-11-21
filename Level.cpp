//project includes
#include "Level.h"
#include "Framework/AssetManager.h"

//library includes
#include <iostream>
#include <fstream>

Level::Level()
	:m_CellSize(64.0f)
	,m_CurrentLevel(0)
	, m_Background()

{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _Target)
{
	//create and update camera
	sf::View Camera = _Target.getDefaultView();

	// Draw game world to the window
	_Target.setView(Camera);

	// TODO Draw game objects
	for (int Y = 0; Y < m_Background.size(); ++Y)
	{
		for (int X = 0; X < m_Background[Y].size(); ++X)
		{
			_Target.draw(m_Background[Y][X]);
		}
	}


	//TODO Adjust camera as needed

	// Reset view
	_Target.setView(_Target.getDefaultView());

}

void Level::Update(sf::Time _FrameTime)
{
	//TODO
}

void Level::LoadLevel(int _LevelToLoad)
{
	//Clean up the old level

	//Delete any data already in the level
	//TODO
	
	//clear out our lists
	m_Background.clear();
	   	  
	//set the current level
	m_CurrentLevel = _LevelToLoad;

	//-=Set up the new level=-

	// Open our file for reading
	std::ifstream inFile;
	std::string fileName = "levels/Level" + std::to_string(m_CurrentLevel) + ".txt";
	inFile.open(fileName);

	// make sure the file was opened
	if (!inFile)
	{
		std::cerr << "Unable to open file " + fileName;
		exit(1); // call system to stop program with error

	}

	// set the starting X and Y coordinates used to position level objects in our new grid system
	int X = 0.0f;
	int Y = 0.0f;

	//Create the first row in our grid
	m_Background.push_back(std::vector<sf::Sprite>());

	// read each character one by one from the file...
	char ch;
	//each time try to read the next character
	//if successful, execute body of loop
	//the "noskipws" means our input from the fill will include
	// the white space(spaces and new lines)
	while (inFile>> std::noskipws >> ch)
	{
		//perform actions based on what character was read in
		if (ch == ' ')
		{
			X += 1;
		}
		else if (ch == '\n')
		{
			++Y;
			X = 0;


			//Create a new row in our grid
			m_Background.push_back(std::vector<sf::Sprite>());
		}
		else
		{
			//this is going to be some object(or empty space),so we need a background
			//create background sprite
			m_Background[Y].push_back(sf::Sprite(AssetManager::GetTexture("graphics/ground.png")));
			m_Background[Y][X].setPosition(X * m_CellSize, Y * m_CellSize);

			 if (ch == '-')
			{
				// do nothing - empty space
			}
			else
			{
				std::cerr << "unrecognised character in level file: " << ch;
			}
		}
	}

	//close the file now that were done with it
	inFile.close();

	}

void Level::ReloadLevel()
{
	LoadLevel(m_CurrentLevel);
}

void Level::LoadNextLevel()
{
	LoadLevel(m_CurrentLevel + 1);
}