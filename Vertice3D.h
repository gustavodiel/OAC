#pragma once

#include <glm\glm.hpp>
#include "Utilities.hpp"

using namespace glm;

class Vertice3D
{
public:
	Vertice3D(vec3 pos) : pos(pos), old_pos(pos), acc(vec3(0, 0, 0)), mass(5), movable(true), accumulated_normal(vec3(0, 0, 0)) {};
	Vertice3D() {};
	~Vertice3D() {};

	void AddForce(vec3 f);

	void OnLoop(double);

	inline vec3 GetPosition() { return this->pos; };

	void ResetAcceleration() { this->acc = vec3(0, 0, 0); };
	void OffsetPosition(const vec3 v) {
		if (this->movable) {
			pos += v;
		}
	};
	void MakeStatic() { this->movable = false; };

	void AddToNormal(vec3 nor) {
		this->accumulated_normal += normalize(nor);
	}

	inline vec3 GetNormal() { return this->accumulated_normal; };  
	void ResetNormal() { this->accumulated_normal = vec3(0, 0, 0); };


private:

	bool movable = true; ///< e movivel

	float mass;

	vec3 pos;
	vec3 old_pos;
	vec3 acc;
	vec3 accumulated_normal;

};

