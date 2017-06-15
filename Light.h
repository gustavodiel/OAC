#pragma once
#include "Entity.h"

class Light :
	public Entity
{
public:
	Light();
	~Light();

	virtual void Initialize();
	virtual void OnLoop(double);
};

