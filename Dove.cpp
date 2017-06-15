#include "stdafx.h"
#include "Dove.h"

#include "Model.h"

Dove::Dove()
= default;


Dove::~Dove()
= default;

/**
\brief Rotina responsavel pela construção do objeto
*/
void Dove::Initialize()
{
	Model *ptrBase = new Model("objs/bird-dove.3DS", "textures/branco.jpg");
	ptrBase->setScale(glm::vec3(2, 2, 2));
	ptrBase->setRotate(vec3(-90, 180, 0));

	this->listOfEntities.push_back(ptrBase);
}