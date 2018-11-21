//project includes
#include "Level.h"
#include "Framework/AssetManager.h"
#include "Wall.h"

//library includes
#include <iostream>
#include <fstream>

Level::Level()
	:m_CellSize(64.0f)
	,m_CurrentLevel(0)
	,m_Background()
	,m_Contents()
{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _Target)
{
	//create and update camera
	sf::View Camera = _Target.getDefaultView();

	//adjust camera as needed
	Camera.setCenter(m_Background[0].size()* m_CellSize/2 ,m_Background.size()*m_CellSize/2);

	// Draw game world to the window
	_Target.setView(Camera);

	// TODO Draw game objects
	for (int y = 0; y < m_Background.size(); ++y)
	{
		for (int x = 0; x < m_Background[y].size(); ++x)
		{
			_Target.draw(m_Background[y][x]);
		}
	}

	//draw grid objects
	//Y = rows
	for (int Y = 0; Y < m_Contents.size(); ++Y)
	{
		//X = Cells
		for (int X = 0; X < m_Contents[Y].size(); ++X)
		{
			//Z = stickoutty(GridObjects)
			for (int Z = 0; Z < m_Contents[Y][X].size(); ++Z)
			{
				m_Contents[Y][X][Z]->Draw(_Target);
			}
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
	
	//Y = rows
	for (int Y = 0; Y < m_Contents.size(); ++ Y)
	{
		//X = Cells
		for (int X = 0; X <  m_Contents[Y].size(); ++X)
		{	
			//Z = stickoutty(GridObjects)
			for (int Z = 0; Z < m_Contents[Z].size(); ++Z)
			{
				delete m_Contents[X][Y][Z];
			}
		}
	}
	
	//clear out our lists
	m_Background.clear();
	m_Contents.clear();

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
	m_Contents.push_back(std::vector< std::vector<GridObject*> >());

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
			m_Contents.push_back(std::vector< std::vector<GridObject*> >());
		}
		else
		{
			//this is going to be some object(or empty space),so we need a background
			//create background sprite
			m_Background[Y].push_back(sf::Sprite(AssetManager::GetTexture("graphics/ground.png")));
			m_Background[Y][X].setPosition(X * m_CellSize, Y * m_CellSize);

			//create an empty vector for our grid contents in this cell
			m_Contents[Y].push_back(std::vector<GridObject*>());

			 if (ch == '-')
			{
				// do nothing - empty space
			}
			 else if (ch =='W')
			 {
				 Wall* wall = new Wall();
				 wall->SetLevel(this);
				 wall->SetGridPosition(X, Y);
				 m_Contents[Y][X].push_back(wall);

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

float Level::GetCellSize()
{
	return m_CellSize;
}