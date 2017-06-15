#pragma once
#include "Entity.h"
class Camera :
	public Entity
{
public:
	Camera();
	~Camera();

	virtual void Initialize() {};

};

