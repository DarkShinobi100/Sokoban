//project includes
#include "Level.h"
#include "Framework/AssetManager.h"
#include "Wall.h"
#include "StorageObject.h"
#include "Player.h"

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
	for (int y = 0; y < m_Contents.size(); ++y)
	{
		//X = Cells
		for (int x = 0; x < m_Contents[y].size(); ++x)
		{
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[y][x].size(); ++z)
			{
				m_Contents[y][x][z]->Draw(_Target);
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
	for (int y = 0; y < m_Contents.size(); ++ y)
	{
		//X = Cells
		for (int x = 0; x <  m_Contents[y].size(); ++x)
		{	
			//Z = stickoutty(GridObjects)
			for (int z = 0; z < m_Contents[z].size(); ++z)
			{
				delete m_Contents[x][y][z];
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

	// set the starting x and y coordinates used to position level objects in our new grid system
	int x = 0.0f;
	int y = 0.0f;

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
			x += 1;
		}
		else if (ch == '\n')
		{
			++y;
			x = 0;


			//Create a new row in our grid
			m_Background.push_back(std::vector<sf::Sprite>());
			m_Contents.push_back(std::vector< std::vector<GridObject*> >());
		}
		else
		{
			//this is going to be some object(or empty space),so we need a background
			//create background sprite
			m_Background[y].push_back(sf::Sprite(AssetManager::GetTexture("graphics/ground.png")));
			m_Background[y][x].setPosition(x * m_CellSize, y * m_CellSize);

			//create an empty vector for our grid contents in this cell
			m_Contents[y].push_back(std::vector<GridObject*>());

			 if (ch == '-')
			{
				// do nothing - empty space
			}
			 else if (ch =='W')
			 {
				 Wall* wall = new Wall();
				 wall->SetLevel(this);
				 wall->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(wall);

			 }
			 else if (ch == 'O')
			 {
				 //if it is a storage Object
				 StorageObject* storageObject = new StorageObject();
				 storageObject->SetLevel(this);
				 storageObject->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(storageObject);

			 }
			 else if (ch == 'P')
			 {
				 //if it is a Player
				 Player* player = new Player();
				 player->SetLevel(this);
				 player->SetGridPosition(x, y);
				 m_Contents[y][x].push_back(player);

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