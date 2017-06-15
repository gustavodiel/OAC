#pragma once
#include "IBehaviour.h"
class WanderBehaviour :
	public IBehaviour
{

	float		fLimitX = 32;
	float		fLimitZ = 32;

	float		fRadius = 0.5f;
	float		fTheta;


public:
	WanderBehaviour();
	~WanderBehaviour();

	virtual void OnLoop(double dDeltaTime) override;
	virtual glm::vec3 GetResultingForce() override;
};

