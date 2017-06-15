#include "stdafx.h"
#include "WanderBehaviour.h"

#include "Vehicle.h"

#include <glm/gtx/vector_angle.hpp>

#include "Utilities.hpp"

WanderBehaviour::WanderBehaviour()
{
	this->fTheta = 0;

	this->limit = 0.075;

	this->vec3Force = glm::vec3(0,0,0);
}


WanderBehaviour::~WanderBehaviour()
{
}

void WanderBehaviour::OnLoop(double dDeltaTime)
{
	float fWanderRadius = 0.5;
	float fWanderDistance = 1;

	this->fTheta += float(Utilities::map(rand()%1000, 0, 1000, -0.5, 0.5));

	glm::vec3 normalizedVel = glm::normalize(ptrVehicle->GetVelocity());
	
	glm::vec3 circlePos = normalizedVel * fWanderDistance + ptrVehicle->getTranslate();

	float h = (glm::angle(normalizedVel, glm::vec3(0, 1, 0))); // TODO: ver :x

	glm::vec3 circleOffset = glm::vec3(
		fWanderRadius * cos(this->fTheta + h),
		0,
		fWanderRadius * sin(this->fTheta + h)
	);

	glm::vec3 target = circlePos + circleOffset;

	this->vec3Force = glm::normalize(target - this->ptrVehicle->getTranslate());

}

glm::vec3 WanderBehaviour::GetResultingForce()
{
	return this->vec3Force;
}
