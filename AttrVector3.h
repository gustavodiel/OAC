#pragma once

#include "PoseAttr.h"
#include <glm/glm.hpp>

class AttrVector3 : public PoseAttr
{
private:
	glm::vec3 Value;

public:
	AttrVector3(double, AttrVector3::AttrName);
	AttrVector3(glm::vec3, double, AttrVector3::AttrName);
	AttrVector3(AttrVector3*);

	void setValue(glm::vec3);

	/**
	\brief Retorna o valor corrente desse atributo animável
	\return valor corrente do atributo
	*/
	inline glm::vec3 getValue() { return this->Value; }

	void updateParent(class Entity *);
};
