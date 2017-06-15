#pragma once

#include "Vertice3D.h"

class Juncao
{
public:
	Juncao(Vertice3D *p1, Vertice3D *p2) : p1(p1), p2(p2) {
		vec3 vec = p1->GetPosition() - p2->GetPosition();
		this->rest_distance = length(vec);
	};
	~Juncao();

	Vertice3D *p1, *p2;

	void LimitarJuncao(double);



private:
	float rest_distance;
};

