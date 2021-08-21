#include "Tree.h"

#include "Tile.h"
#include "Game.h"
#include "DeltaTime.h"

#include <iostream>

void Tree::Init(Game* _game)
{
	game = _game;
	fatherNode = nullptr;
	agent.Init();
	agent.SetSteeringBehavior(BEHAVIOR::PATH_FOLLOWING);
}

void Tree::Update()
{
	//one step of a serching type is made every Update
	t += gl::DeltaTime::GetDeltaTime();
	if (true == searching && t > intervalTime)
	{
		switch (searchingType)
		{
		case SEARCHING_TYPE::NONE:
			std::cout << "It's seraching nothing? wtf" << std::endl;
			break;
		case SEARCHING_TYPE::BF:
			BFSearch();
			break;
		case SEARCHING_TYPE::DF:
			DFSearch();
			break;
		case SEARCHING_TYPE::DIJKSTRA:
			break;
		case SEARCHING_TYPE::BEST:
			break;
		case SEARCHING_TYPE::ASTAR:
			break;
		}

		t = 0;
	}
	if (followPath == true)
	{
		agent.Update();
	}
}

void Tree::ProcessEvents()
{
}

void Tree::Render(sf::RenderWindow* window)
{
	agent.Render(window);
}

void Tree::Destroy()
{
}

void Tree::SearchByType(Tile* _tree, SEARCHING_TYPE _serachType)
{
	//It need to update, for it to do the search
	if (searching == true && searchingType != SEARCHING_TYPE::NONE && fatherNode != nullptr) {
		std::cout << "It's allraedy searching, u can't serach now" << std::endl;
		return;
	}
	if (_serachType == SEARCHING_TYPE::NONE || _tree == nullptr) {
		std::cout << "The tree or search type its nothing..." << std::endl;
		return;
	}

	searchingType = _serachType;
	fatherNode = _tree;
	searching = true;
	currentNodes.push_back(fatherNode);
}

void Tree::BFSearch()
{
	//when its over: searching = false; searchingType = NONE; fatherNode = nullptr; //*Dont Delete the tree memory
	//bool clearCuurentNode = true;

	std::vector<Tile*> cAux;
	int size = currentNodes.size();
	for (int i = 0; i < size; i++)
	{
		// ---------- Node Up
		if (currentNodes[i]->nodeUp != nullptr && currentNodes[i]->nodeUp->GetType() == TILE_TYPE::TARGET) // found the target
		{
			target = currentNodes[i]->nodeUp;
			searching = false;
			searchingType = SEARCHING_TYPE::NONE;
			//fatherNode = nullptr;
			CreateRoute();
			break;
		}
		// ---------- Node down
		if (currentNodes[i]->nodeDown != nullptr && currentNodes[i]->nodeDown->GetType() == TILE_TYPE::TARGET) // found the target
		{
			target = currentNodes[i]->nodeDown;
			searching = false;
			searchingType = SEARCHING_TYPE::NONE;
			//fatherNode = nullptr;
			CreateRoute();
			break;
		}
		// ---------- Node Left
		if (currentNodes[i]->nodeLeft != nullptr && currentNodes[i]->nodeLeft->GetType() == TILE_TYPE::TARGET) // found the target
		{
			target = currentNodes[i]->nodeLeft;
			searching = false;
			searchingType = SEARCHING_TYPE::NONE;
			//fatherNode = nullptr;
			CreateRoute();
			break;
		}
		// ---------- Node Right
		if (currentNodes[i]->nodeRight != nullptr && currentNodes[i]->nodeRight->GetType() == TILE_TYPE::TARGET) // found the target
		{
			target = currentNodes[i]->nodeRight;
			searching = false;
			searchingType = SEARCHING_TYPE::NONE;
			//fatherNode = nullptr;
			CreateRoute();
			break;
		}



		// ---------- Node Up
		if (currentNodes[i]->nodeUp != nullptr && currentNodes[i]->nodeUp->GetType() == TILE_TYPE::EMPTY)
		{
			currentNodes[i]->nodeUp->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
			cAux.push_back(currentNodes[i]->nodeUp);
		}
		// ---------- Node down
		if (currentNodes[i]->nodeDown != nullptr && currentNodes[i]->nodeDown->GetType() == TILE_TYPE::EMPTY) // found the target
		{
			currentNodes[i]->nodeDown->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
			cAux.push_back(currentNodes[i]->nodeDown);
		}
		// ---------- Node Left
		if (currentNodes[i]->nodeLeft != nullptr && currentNodes[i]->nodeLeft->GetType() == TILE_TYPE::EMPTY)
		{
			currentNodes[i]->nodeLeft->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
			cAux.push_back(currentNodes[i]->nodeLeft);
		}
		// ---------- Node Right
		if (currentNodes[i]->nodeRight != nullptr && currentNodes[i]->nodeRight->GetType() == TILE_TYPE::EMPTY)
		{
			currentNodes[i]->nodeRight->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
			cAux.push_back(currentNodes[i]->nodeRight);
		}
	}

	//clear the nodes that i don't need anymore
	currentNodes.clear();
	for (int i = 0; i < cAux.size(); i++)
	{
		currentNodes.push_back(cAux[i]);
	}
	cAux.clear();
	//search the 4 nodes of all your current children, if there is no more where to find, en it 
}



void Tree::DFSearch()
{
	//when its over: searching = false; searchingType = NONE; fatherNode = nullptr; //*Dont Delete the tree memory
	//bool clearCuurentNode = true;

	std::vector<Tile*> cAux;
	int i = currentNodes.size() - 1;

	// ---------- Node Up
	if (currentNodes[i]->nodeUp != nullptr && currentNodes[i]->nodeUp->GetType() == TILE_TYPE::TARGET) // found the target
	{
		target = currentNodes[i]->nodeUp;
		searching = false;
		searchingType = SEARCHING_TYPE::NONE;
		//fatherNode = nullptr;
		CreateRoute();
		return;
	}
	else if (currentNodes[i]->nodeUp != nullptr && currentNodes[i]->nodeUp->GetType() == TILE_TYPE::EMPTY)
	{
		currentNodes[i]->nodeUp->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
		currentNodes.push_back(currentNodes[i]->nodeUp);
		return;
	}


	// ---------- Node down
	if (currentNodes[i]->nodeDown != nullptr && currentNodes[i]->nodeDown->GetType() == TILE_TYPE::TARGET) // found the target
	{
		target = currentNodes[i]->nodeDown;
		searching = false;
		searchingType = SEARCHING_TYPE::NONE;
		//fatherNode = nullptr;
		CreateRoute();
		return;
	}
	else if (currentNodes[i]->nodeDown != nullptr && currentNodes[i]->nodeDown->GetType() == TILE_TYPE::EMPTY) // found the target
	{
		currentNodes[i]->nodeDown->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
		currentNodes.push_back(currentNodes[i]->nodeDown);
		return;
	}


	// ---------- Node down
	if (currentNodes[i]->nodeLeft != nullptr && currentNodes[i]->nodeLeft->GetType() == TILE_TYPE::TARGET) // found the target
	{
		target = currentNodes[i]->nodeLeft;
		searching = false;
		searchingType = SEARCHING_TYPE::NONE;
		//fatherNode = nullptr;
		CreateRoute();
		return;
	}
	else if (currentNodes[i]->nodeLeft != nullptr && currentNodes[i]->nodeLeft->GetType() == TILE_TYPE::EMPTY)
	{
		currentNodes[i]->nodeLeft->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
		currentNodes.push_back(currentNodes[i]->nodeLeft);
		return;
	}


	// ---------- Node Right
	if (currentNodes[i]->nodeRight != nullptr && currentNodes[i]->nodeRight->GetType() == TILE_TYPE::TARGET) // found the target
	{
		target = currentNodes[i]->nodeRight;
		searching = false;
		searchingType = SEARCHING_TYPE::NONE;
		//fatherNode = nullptr;
		CreateRoute();
		return;
	}

	else if (currentNodes[i]->nodeRight != nullptr && currentNodes[i]->nodeRight->GetType() == TILE_TYPE::EMPTY)
	{
		currentNodes[i]->nodeRight->ChangeObjectType(TILE_TYPE::PLAYER_INSTANCE);
		currentNodes.push_back(currentNodes[i]->nodeRight);
		return;
	}


	//search the 4 nodes of all your current children, if there is no more where to find, en it 
}

void Tree::DijkstraFind()
{
	//when its over: searching = false; searchingType = NONE; fatherNode = nullptr; //*Dont Delete the tree memory
}

void Tree::BestFind()
{
	//when its over: searching = false; searchingType = NONE; fatherNode = nullptr; //*Dont Delete the tree memory
}

void Tree::AStarFind()
{
	//when its over: searching = false; searchingType = NONE; fatherNode = nullptr; //*Dont Delete the tree memory
}

void Tree::CreateRoute()
{
	Tile* auxT = target->nodeFather;

	while (true)
	{
		if (auxT->GetType() != TILE_TYPE::PLAYER)
		{
			//set a path point in auxT coordinades ultil find the player
			auxT->ChangeObjectType(TILE_TYPE::ROAD);
			auxT = auxT->nodeFather;
		}
		else
		{
			break;
		}
		
	}/**/

	agent.SetSteeringBehavior(BEHAVIOR::SEEK);
	followPath = true;
}

