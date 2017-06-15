#pragma once

#include "Entity.h"

class Entity2D: public Entity
{
public:
	Entity2D();
	~Entity2D();


	virtual void OnPreRender(glm::mat4) override;


	virtual void OnRender(glm::mat4) override;


	virtual void LoadDimensions() override;


	virtual void OnLoop(double) override;

};

