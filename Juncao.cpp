#include "stdafx.h"
#include "Juncao.h"

#include <glm/glm.hpp>

using namespace glm;

Juncao::~Juncao()
{
}

void Juncao::LimitarJuncao(double elapse) {
	vec3 p1_to_p2 = p2->GetPosition() - p1->GetPosition();
	float curr_dist = length(p1_to_p2);


	vec3 correctionVector = p1_to_p2 * (1 - rest_distance / curr_dist);
	vec3 correctionVectorHalf = correctionVector * 0.9f * (float)elapse;
	p1->OffsetPosition(correctionVectorHalf);
	p2->OffsetPosition(-correctionVectorHalf);
}