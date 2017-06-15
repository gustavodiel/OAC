#pragma once
class SteeringGroup
{
	enum PositionPlacement
	{
		Circle = 0,
		Circle2,
		Square
	};
protected:
	int							iGroupSize = 50;

	const char*					strModelName;

	class Entity*				ptrLeader;
	class Entity*				ptrTarget;
public:
	SteeringGroup();
	~SteeringGroup();
};

