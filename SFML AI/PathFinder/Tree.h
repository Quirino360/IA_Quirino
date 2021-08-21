#pragma once
#include <SFML/Graphics.hpp>
#include "AI.h"

enum class SEARCHING_TYPE
{
	NONE = -1,
	BF,
	DF,
	BEST,
	DIJKSTRA,
	ASTAR,
};

class Tile;
class Game;

//This class is to suport the map tiles, making all the work needed
class Tree
{
public:
	Tree() = default;
	~Tree() = default;

	// ---------- Game Pipeline
	void Init(Game* _game);
	void Update();
	void ProcessEvents();
	void Render(sf::RenderWindow* window);
	void Destroy();


private:
	// ---------- Searching Vars
	bool searching = false;
	SEARCHING_TYPE searchingType = SEARCHING_TYPE::NONE;
	Tile* fatherNode = nullptr;
	std::vector<Tile*> currentNodes;

	// Game Pointer
	Game* game = nullptr;

	//Every n time 
	sf::Time time;
	float t = 0;
	float intervalTime = 0.2;

	// Tatrget
	Tile* target = nullptr;

	//Agent 
	gl::AI agent;
	bool followPath = true;

public:
	//Find target by search type
	void SearchByType(Tile* tree, SEARCHING_TYPE _serachType);
	//Find Shortest & Fastest Route

	// ---------- Geter
	gl::AI& GetAgent() { return agent; };

	// ---------- Seter

private:
	// BFS - DFS - Dijkstra - Best - AStar
	void BFSearch();
	void DFSearch();
	void DijkstraFind();
	void BestFind();
	void AStarFind();

	void CreateRoute();
};

