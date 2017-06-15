#pragma once
#include "IBehaviour.h"
class StayWithin :
	public IBehaviour
{
protected:
	int startX = -16;
	int startY = 0;
	int endX = 16;
	int endY = 16;

public:
	StayWithin();
	~StayWithin();

	virtual void OnLoop(double dDeltaTime) override;
	virtual glm::vec3 GetResultingForce() override;

};

