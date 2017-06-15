#pragma once
#include <glm\glm.hpp>

#include <vector>

class IBehaviour {
public:
	class Vehicle*		ptrVehicle;
	glm::vec3			vec3Force;
	float limit = 1.0f;


	virtual void OnLoop(double dDeltaTime) = 0;

	virtual glm::vec3 GetResultingForce() = 0;

	void setVechicle(Vehicle* veh) { this->ptrVehicle = veh; };

	float GetLimit() { return this->limit; };

};

