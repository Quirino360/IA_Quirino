#include "Map.h"

#include "Tile.h"
#include "Game.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init(Game* _game, sf::Vector2f _mapSize)
{
	//Get the game instance
	game = _game;

	// Init tree 
	tree.Init(_game);

	// Set map
	mapSize = _mapSize;
	tilesSize = { 25, 25 };
	sf::Vector2f startingPos = { 250, 250 };
	sf::Vector2f posAux = startingPos;

	// Initialize tiles
	for (unsigned int x = 0; x < mapSize.x; x++)
	{
		mapTiles.push_back(std::vector<Tile*>());
		for (unsigned int y = 0; y < mapSize.y; y++)
		{
			mapTiles[x].push_back(new Tile());
			mapTiles[x][y]->Init(game, tilesSize);
			mapTiles[x][y]->SetPosition(posAux);
			
			mapTiles[x][y]->SetCoordinades({ static_cast<float>(x), static_cast<float>(y) });
			mapTiles[x][y]->SetID(std::to_string(x) + " " + std::to_string(y));
			posAux += sf::Vector2f(tilesSize.x, 0);
		}
		posAux += sf::Vector2f(-posAux.x + startingPos.x, tilesSize.y);
	}
	//Player
	mapTiles[0][0]->SetType(TILE_TYPE::PLAYER);
	player = mapTiles[0][0];

	//Goal
	mapTiles[mapSize.x - 1][mapSize.y - 1]->SetType(TILE_TYPE::TARGET);
	goal = mapTiles[mapSize.x - 1][mapSize.y - 1];
	
	//Set the nodes depending on the father, so if the player changes, the tree changes
	Map::SetNodes(); //idw why but i have to tell that i call this function from Map

	//What serach type do after getting the father
	//tree.SearchByType(fatherNode, SEARCHING_TYPE::BREADTH);

}

void Map::Update()
{
	for (unsigned int x = 0; x < mapSize.x; x++)
	{
		for (unsigned int y = 0; y < mapSize.y; y++)
		{
			UpdateTile(mapTiles[x][y]);
		}
	}

	tree.Update();

	/*// Make Breathd First
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
	{
		tree.SearchByType(fatherNode, SEARCHING_TYPE::BF);
	}
	// Make Breathd First
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	{
		tree.SearchByType(fatherNode, SEARCHING_TYPE::DF);
	}/**/
}

void Map::ProcessEvents()
{
}

void Map::Render(sf::RenderWindow* window)
{
	//Render the tiles
	for (unsigned int x = 0; x < mapSize.x; x++)
	{
		for (unsigned int y = 0; y < mapSize.y; y++)
		{
			mapTiles[x][y]->Render(window);
		}
	}

	tree.Render(window);
}

void Map::Destroy()
{
}

void Map::ResetMapNodes()
{
	for (unsigned int x = 0; x < mapSize.x; x++)
	{
		for (unsigned int y = 0; y < mapSize.y; y++)
		{
			mapTiles[x][y]->nodeFather = nullptr;
			mapTiles[x][y]->nodeUp = nullptr;
			mapTiles[x][y]->nodeDown = nullptr;
			mapTiles[x][y]->nodeLeft = nullptr;
			mapTiles[x][y]->nodeRight = nullptr;
		}
	}
}

void Map::ResetMapTypes()
{
	for (unsigned int x = 0; x < mapSize.x; x++)
	{
		for (unsigned int y = 0; y < mapSize.y; y++)
		{
			if (mapTiles[x][y]->GetType() != TILE_TYPE::PLAYER && mapTiles[x][y]->GetType() != TILE_TYPE::TARGET)
			{
				mapTiles[x][y]->SetType(TILE_TYPE::EMPTY);
			}
		}
	}
	tree.Init(game);
	ResetMapNodes();
	SetNodes();
}

void Map::UpdateTile(Tile* _tile)
{
	_tile->Update();

	//Change Player Position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && _tile->IsMouseOver() && _tile->GetType() == TILE_TYPE::EMPTY)
	{
		ResetMapNodes();
		player->SetType(TILE_TYPE::EMPTY);
		player = _tile;
		fatherNode = player;
		player->SetType(TILE_TYPE::PLAYER);
		Map::SetNodes();
	}

	//Change Goal Position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && _tile->IsMouseOver() && _tile->GetType() == TILE_TYPE::EMPTY)
	{
		goal->SetType(TILE_TYPE::EMPTY);
		goal = _tile;
		goal->SetType(TILE_TYPE::TARGET);
		Map::SetNodes();
	}

	//make it a wall if its empty
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _tile->IsMouseOver() && _tile->GetType() == TILE_TYPE::EMPTY)
	{
		_tile->SetType(TILE_TYPE::WALL);
		Map::SetNodes();
	}

	//make it empty if it is a wall
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && _tile->IsMouseOver() && _tile->GetType() == TILE_TYPE::WALL)
	{
		_tile->SetType(TILE_TYPE::EMPTY);
		Map::SetNodes();
	}

}

void Map::SetNodes()
{
	// Set nodes *The first node is the father node* *Change the father node, will be the starting tile*

	if (fatherNode == nullptr)
	{
		fatherNode = mapTiles[0][0];
	}
	ResetMapNodes();
	tree.GetAgent().SetPosition(fatherNode->GetPosition());

	// Set the tree father with the new position		
	// This go over from right to down of the father node
	std::vector<Tile*> currentNodes;
	currentNodes.push_back(fatherNode);

	for (unsigned int x = 0; x < mapSize.x; x++)
	{
		for (unsigned int y = 0; y < mapSize.y; y++)
		{
			mapTiles[x][y]->seted = false;
		}
	}

	for (int i = 0; i < currentNodes.size();)
	{
		int x = currentNodes[i]->GetCoordinades().x;
		int y = currentNodes[i]->GetCoordinades().y;

		if (currentNodes[i]->seted == true) 
		{
			currentNodes.erase(currentNodes.begin() + i);
			continue;
		}


		// Node Left //
		if (x >= 0 && x < mapSize.x && y - 1 >= 0 && y - 1 < mapSize.y)
		{
			if (mapTiles[x][y - 1]->GetType() != TILE_TYPE::WALL)
			{
				currentNodes[i]->nodeLeft = mapTiles[x][y - 1];
				if (currentNodes[i]->nodeLeft->nodeFather == nullptr)
				{
					currentNodes[i]->nodeLeft->nodeFather = currentNodes[i];
				}
				if (mapTiles[x][y - 1]->seted == false)
				{
					currentNodes.push_back(currentNodes[i]->nodeLeft);
				}
			}
		}

		// Node Right //
		if (x >= 0 && x < mapSize.x && y + 1 >= 0 && y + 1 < mapSize.y)
		{
			if (mapTiles[x][y + 1]->GetType() != TILE_TYPE::WALL)
			{
				currentNodes[i]->nodeRight = mapTiles[x][y + 1];
				if (currentNodes[i]->nodeRight->nodeFather == nullptr)
				{
					currentNodes[i]->nodeRight->nodeFather = currentNodes[i];
				}
				if (mapTiles[x][y + 1]->seted == false)
				{
					currentNodes.push_back(currentNodes[i]->nodeRight);
				}
			}
		}

		// Node Down //
		if (x + 1 >= 0 && x + 1 < mapSize.x && y >= 0 && y < mapSize.y)
		{
			if (mapTiles[x + 1][y]->GetType() != TILE_TYPE::WALL)
			{
				currentNodes[i]->nodeDown = mapTiles[x + 1][y];
				if (currentNodes[i]->nodeDown->nodeFather == nullptr)
				{
					currentNodes[i]->nodeDown->nodeFather = currentNodes[i];
				}
				if (mapTiles[x + 1][y]->seted == false) // IDW why dis doesnt work 
				{
					currentNodes.push_back(currentNodes[i]->nodeDown);
				}
			}
		}

		// Node Up //
		if (x - 1 >= 0 && x - 1 < mapSize.x && y >= 0 && y < mapSize.y)
		{
			if (mapTiles[x - 1][y]->GetType() != TILE_TYPE::WALL)
			{
				currentNodes[i]->nodeUp = mapTiles[x - 1][y];
				if (currentNodes[i]->nodeUp->nodeFather == nullptr)
				{
					currentNodes[i]->nodeUp->nodeFather = currentNodes[i];
				}
				if (mapTiles[x - 1][y]->seted == false)
				{
					currentNodes.push_back(currentNodes[i]->nodeUp);
				}
			}
		}

		currentNodes[i]->seted = true;
		currentNodes.erase(currentNodes.begin() + i);
	}
	
}
/*/**/



	//Maybe in one for make just the fathers and the make the childs 