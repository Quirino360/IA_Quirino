#pragma once
#include "Object.h"
class Actor :  public Object
{
public:

	virtual void Update();
	virtual void Init();
	virtual void Render();
	virtual void Destroy();
};

