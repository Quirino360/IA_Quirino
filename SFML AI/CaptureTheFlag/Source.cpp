#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	auto& gameObj = GetGameObj();
	gameObj.run();

	return 0;
}