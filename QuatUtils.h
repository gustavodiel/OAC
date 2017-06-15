#pragma once

#include <glm\glm.hpp>
#include <glm\ext.hpp>

using namespace glm;

class QuatUtils
{
public:
	QuatUtils();
	~QuatUtils();

	static quat RotationBetweenVectors(vec3 start, vec3 dest);

	static quat LookAt(vec3 direction, vec3 desiredUp);

	static quat RotateTowards(quat q1, quat q2, float maxAngle);
};

