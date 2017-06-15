#include "stdafx.h"
#include "AvoidObstacleBehaviour.h"

#include "Vehicle.h"

AvoidObstacleBehaviour::AvoidObstacleBehaviour(std::vector<Entity*> list)
{
	this->listOfEntitiesToAvoid = list;
	this->limit = 1.0f;
}


AvoidObstacleBehaviour::~AvoidObstacleBehaviour()
{
}

void AvoidObstacleBehaviour::OnLoop(double dDeltaTime) {
	glm::vec3 sum(0);
	int count = 0;

	for (auto other : this->listOfEntitiesToAvoid) {

		float d = glm::distance(this->ptrVehicle->getTranslate(), other->getTranslate());

		if ((d > 0) && (d < this->fDistanceToActivate)) {
			glm::vec3 diff = this->ptrVehicle->getTranslate() - other->getTranslate();
			diff = glm::normalize(diff) / d;
			sum += diff;
			count++;
		}
	}

	if (count > 0) {
		sum /= count;
	}
	this->vec3Force = sum;
}

glm::vec3 AvoidObstacleBehaviour::GetResultingForce() {
	return this->vec3Force;
}