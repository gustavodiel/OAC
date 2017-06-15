#include "stdafx.h"
#include "SeekBehaviour.h"

#include "Vehicle.h"

#include "Constants.h"
#include "Camera.h"
#include "Application.h"
#include "Utilities.hpp"

SeekBehaviour::SeekBehaviour(Entity* entTarget) {
	this->vec3Force = glm::vec3(0, 0, 0);
	this->ptrTarget = entTarget;

	this->limit = Utilities::map(rand() % 1000, 0, 1000, 0.05, 0.20);
}

SeekBehaviour::SeekBehaviour()
{
	this->vec3Force = glm::vec3(0, 0, 0);

	this->limit = 1.0f;
}


SeekBehaviour::~SeekBehaviour()
{
}

glm::vec3 SeekBehaviour::GetResultingForce() {
	return this->vec3Force;
}

void SeekBehaviour::OnLoop(double dDeltaTime) {
	// Calculate Target!	
	this->vec3Force = (this->ptrTarget->getTranslate() - this->ptrVehicle->getTranslate());

}
