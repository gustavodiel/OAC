#include "stdafx.h"
#include "Vertice3D.h"

#define DAMPING 0.45 // how much to damp the cloth simulation each frame

void Vertice3D::OnLoop(double dDeltaTime) {
	if (movable) {
		vec3 temp = pos;
		float damping = DAMPING * dDeltaTime;
		damping = min(damping, 1.0f);
		this->pos +=  (pos - old_pos) * float(1.0f - damping) + this->acc * (float)dDeltaTime;
		this->old_pos = temp;
		this->acc = vec3(0, 0, 0);
	}

}

void Vertice3D::AddForce(vec3 f) {

	this->acc += f / this->mass;
}