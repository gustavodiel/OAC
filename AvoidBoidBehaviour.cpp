#include "stdafx.h"
#include "AvoidBoidBehaviour.h"

#include "Vehicle.h"

#include "Constants.h"
#include "Application.h"

AvoidBoidBehaviour::AvoidBoidBehaviour()
{
	this->limit = 0.8f;
}


AvoidBoidBehaviour::~AvoidBoidBehaviour()
{
}


void AvoidBoidBehaviour::OnLoop(double dDeltaTime) {
	float fDesiredDistance = this->ptrVehicle->getRadius() * 1.5;
	glm::vec3 sum(0);
	int count = 0;

	for (Vehicle* other : ptrApp->getVehicles()) {

		if (other == this->ptrVehicle) continue; // Dont do this for youself :)

		float d = glm::distance(this->ptrVehicle->getTranslate(), other->getTranslate());
		if ((d > 0) && (d < fDesiredDistance)) {
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

glm::vec3 AvoidBoidBehaviour::GetResultingForce() {
	return this->vec3Force;
}