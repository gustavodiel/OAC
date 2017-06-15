#pragma once
#include "IBehaviour.h"
class AvoidBoidBehaviour :
	public IBehaviour
{
public:
	AvoidBoidBehaviour();
	~AvoidBoidBehaviour();

	virtual void OnLoop(double dDeltaTime);
	virtual glm::vec3 GetResultingForce();
};

