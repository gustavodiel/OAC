#pragma once

#include "IBehaviour.h"

#include "Entity.h"

class RandomWalker : public IBehaviour
{
protected:
	std::vector<Entity*> ptrCollisionEntities;
public:
	RandomWalker();
	~RandomWalker();

	virtual void OnLoop(double dDeltaTime);

	virtual glm::vec3 GetResultingForce();

	void addCollisionEntity(Entity* ent) { this->ptrCollisionEntities.push_back(ent); };
};

