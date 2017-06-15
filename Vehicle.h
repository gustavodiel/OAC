#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "IBehaviour.h"

#include "Entity.h"

class Vehicle
{
protected:
	glm::vec3	vec3Velocity,
		vec3Acc;

	double radius;
	float maxSpeed;
	float maxForce;

	Entity* ptrEntity;

	std::vector<class IBehaviour*> behaviours;

public:
	Vehicle(Entity*);
	~Vehicle();

	void OnLoop(double dDeltaTime);

	void AddBehaviour(class IBehaviour*);

	inline glm::vec3 getTranslate() { return this->ptrEntity->GetWorldPosition(); };
	inline float getRadius() { return this->radius; };
	inline float getMaxSpeed() { return this->maxSpeed; };
	inline glm::vec3 GetVelocity() { return this->vec3Velocity; };

	inline void SetVelocity(glm::vec3 vel) { this->vec3Velocity = vel; };
	inline void SetMaxSpeed(float speed) { this->maxSpeed = speed; };

};

