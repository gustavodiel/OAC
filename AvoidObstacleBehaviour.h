#pragma once
#include "IBehaviour.h"

#include <vector>
#include "Entity.h"

class AvoidObstacleBehaviour :
	public IBehaviour
{

protected:

	std::vector<Entity*>		listOfEntitiesToAvoid;
	float						fDistanceToActivate = 2.0f;

public:
	AvoidObstacleBehaviour(std::vector<Entity*> list);
	~AvoidObstacleBehaviour();

	virtual void OnLoop(double dDeltaTime) override;
	virtual glm::vec3 GetResultingForce() override;
};

