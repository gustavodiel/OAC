#include "stdafx.h"
#include "Headphone.h"

#include "Model.h"

Headphone::Headphone()
{
}


Headphone::~Headphone()
{
}


void Headphone::Initialize() {
	Model *ptrBase = new Model("objs/headphones.obj", "textures/headphones.jpg");
	this->listOfEntities.push_back(ptrBase);
}