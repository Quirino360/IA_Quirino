#pragma once
#include "Object.h"
class Actor :  public Object
{
public:
	Actor();
	virtual ~Actor() = 0;

	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	//sf::Shape* shape;
};

