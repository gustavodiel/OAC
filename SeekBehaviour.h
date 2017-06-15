#pragma once

#include "IBehaviour.h"

#include "Entity.h"

class SeekBehaviour : public IBehaviour
{
protected:

	Entity*			ptrTarget;
	
public:
	SeekBehaviour();
	SeekBehaviour(Entity* target);
	~SeekBehaviour();

	virtual void OnLoop(double dDeltaTime);

	virtual glm::vec3 GetResultingForce();

	void SetTarget(Entity* target) { this->ptrTarget = target; };
};

