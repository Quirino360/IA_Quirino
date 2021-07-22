#pragma once
#include <SFML/Graphics.hpp>

/**
* @brief   Father of all objects, wthis will only have main functions	*/
class Object
{
public:
	Object();
	virtual ~Object();

protected:
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

};

