#include "stdafx.h"
#include "BodyMember.h"

#include "Model.h"

void BodyMember::Initialize() {

	Model *ptrBase = new Model("objs/box.obj" , this->myCor);
	this->listOfEntities.push_back(ptrBase);
}