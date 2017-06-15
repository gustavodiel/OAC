#include "stdafx.h"
#include "Vehicle.h"

#include "Utilities.hpp"

#include "Constants.h"
#include "Application.h"
#include "Camera.h"

#include <glm/gtx/vector_angle.hpp>

Vehicle::Vehicle(Entity* ent)
{
	this->ptrEntity = ent;
	ent->setVehicle(this);

	this->vec3Acc = glm::vec3(0, 0, 0);

	//this-> = glm::vec3(0, 0, 0);

	this->vec3Velocity = glm::vec3(Utilities::map(rand() % 1000, 0, 1000, -0.2, 0.2), 0, Utilities::map(rand() % 1000, 0, 1000, -0.2, 0.2));

	this->radius = 0.5;
	this->maxSpeed = 0.025;
	this->maxForce = 0.25;

	ptrApp->AddVehicle(this);
}


Vehicle::~Vehicle()
{
}

void Vehicle::OnLoop(double dDeltaTime) {
	for (auto behaviour : this->behaviours) {
		behaviour->OnLoop(dDeltaTime);

		this->vec3Acc += Utilities::limit(behaviour->GetResultingForce() * this->maxForce - this->vec3Velocity, behaviour->GetLimit());
	}

	this->vec3Velocity += this->vec3Acc * (float)dDeltaTime;
	this->vec3Velocity = Utilities::limit(this->vec3Velocity, this->maxSpeed);

	this->vec3Velocity.y = 0.0f;

	this->ptrEntity->setTranslate(this->ptrEntity->getTranslate() + this->vec3Velocity);

	//float h = glm::angle(this->vec3Velocity, glm::vec3(1, 0, 0)); // TODO: ver :x

	//this->ptrEntity->setOrientation(glm::angleAxis(h, glm::vec3(0.f, 1.f, 0.f))); this->vec3Velocity
	this->ptrEntity->setOrientation(glm::toQuat(glm::inverse(glm::lookAt(this->ptrEntity->getTranslate(), this->ptrEntity->getTranslate() + this->vec3Velocity, glm::vec3(0.0f, 1.0f, 0.0f)))));
	//setRotate(vec3(0, h, 0));

	this->vec3Acc *= 0.0f;

}

void Vehicle::AddBehaviour(IBehaviour *behaviour)
{
	behaviour->setVechicle(this);
	behaviours.push_back(behaviour);
}
