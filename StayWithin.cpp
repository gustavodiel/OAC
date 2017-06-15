#include "stdafx.h"
#include "StayWithin.h"

#include "Vehicle.h"

StayWithin::StayWithin()
{
	this->limit = 7.5f;
}


StayWithin::~StayWithin()
= default;

void StayWithin::OnLoop(double dDeltaTime)
{
	glm::vec3 desired;
	bool saiu = false;
	glm::vec3 position = this->ptrVehicle->getTranslate();
	glm::vec3 vel = this->ptrVehicle->GetVelocity();

	if (position.x > endX) {
		desired = glm::vec3(-ptrVehicle->getMaxSpeed(), 0, vel.z);
		saiu = true;
	} else if (position.x < startX) {
		desired = glm::vec3(ptrVehicle->getMaxSpeed(), 0, vel.z);
		saiu = true;
	}

	if (position.z > endY) {
		desired = glm::vec3(vel.x, 0, -ptrVehicle->getMaxSpeed());
		saiu = true;
	}
	else if (position.z < startY) {
		desired = glm::vec3(vel.x, 0, ptrVehicle->getMaxSpeed());
		saiu = true;
	}
	if (saiu) {
		this->vec3Force = glm::normalize(desired) * ptrVehicle->getMaxSpeed();
	}

}

glm::vec3 StayWithin::GetResultingForce()
{
	return this->vec3Force;
}
