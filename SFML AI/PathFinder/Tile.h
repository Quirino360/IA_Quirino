#pragma once
#include <SFML/Graphics.hpp>

enum class TILE_TYPE
{
	EMPTY = 0,
	WALL,
	PLAYER,
	PLAYER_INSTANCE,
	TARGET,
	ROAD
};

class Game;

class Tile
{
public:
	Tile();
	virtual ~Tile();

	virtual void Init(Game* _game, sf::Vector2f _size = { 50.0f, 50.0f }, TILE_TYPE _type = TILE_TYPE::EMPTY);
	virtual void Update();
	virtual void ProcessEvents();
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();
	
	//Parent
	Tile* nodeFather = nullptr;

	//Children
	Tile* nodeUp = nullptr;
	Tile* nodeDown = nullptr;
	Tile* nodeLeft = nullptr;
	Tile* nodeRight = nullptr;


	//weights of nodes
	float leftWeight = 0.0f;
	float rightWeight = 0.0f;

	//
	bool seted = false;

private:
	sf::RectangleShape rShape;
	TILE_TYPE tileType = TILE_TYPE::EMPTY;

	sf::Vector2f coordinates;
	std::string ID = ""; //The id is the coordinate x y 

	//Game pointer
	Game* game;

public:
	bool IsMouseOver();
	void SetColorByType(TILE_TYPE _tileType);
	void ChangeObjectType(TILE_TYPE _tileType);

	/*			Geters			*/
	sf::Vector2f GetCoordinades() { return coordinates; };
	sf::Vector2f GetPosition() { return rShape.getPosition(); };
	sf::Vector2f GetSize() { return rShape.getPosition(); }
	std::string GetID() { return ID; };
	TILE_TYPE GetType() { return tileType; };

	/*			Seters			*/
	void SetCoordinades(sf::Vector2f _coordinates) { coordinates = _coordinates; };
	void SetPosition(sf::Vector2f _newPos) { rShape.setPosition(_newPos); };
	void SetSize(sf::Vector2f _size) { rShape.setSize(_size); rShape.setOrigin({ _size.x / 2, _size.y / 2 }); };
	void SetID(std::string _ID) { ID = _ID; };
	void SetType(TILE_TYPE _tileType) { tileType = _tileType; SetColorByType(tileType); };
private:




};

