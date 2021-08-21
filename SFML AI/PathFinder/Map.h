#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Tree.h"

class Tile;
class Game;

class Map
{
public:
	Map();
	~Map();

	// ---------- Game Pipeline
	void Init(Game* _game, sf::Vector2f _mapSize = { 25, 25 });
	void Update();
	void ProcessEvents();
	void Render(sf::RenderWindow* window);
	void Destroy();

private:
	// ---------- Map & tiles
	std::vector<std::vector<Tile*>> mapTiles;
	// Map
	sf::Vector2f mapSize;
	//Tiles
	sf::Vector2f tilesSize;
	Tile* player;
	Tile* goal;

	// ---------- Tree
	Tree tree;
	Tile* fatherNode; //from this you can get the whole three // Its also mapTiles[0][0]


	//Game pointer
	Game* game;

public:
	//Makes all tiles to TilyType::nothing except, The player & Goal
	void ResetMapNodes();
	void ResetMapTypes();

	// ---------- Getters
	sf::Vector2f GetMapSize() { return mapSize; };
	Tree& GetTree() { return tree; };
	Tile* GetFatherNode() { return fatherNode; };

	// ---------- Setters
	void SetMapSize(sf::Vector2f _mapSize) { mapSize = _mapSize; };

private:
	void UpdateTile(Tile* _tile);
	void SetNodes();

};

