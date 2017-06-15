#include "stdafx.h"
#include "Light.h"

#include "Animator.h"


Light::Light()
{
	this->Initialize();
}


Light::~Light()
{
}

void Light::Initialize() {

}

void Light::OnLoop(double dDeltaTime) {

	if (this->ptrAnimator) {
		this->ptrAnimator->OnLoop(dDeltaTime);
	}

	Entity::OnLoop(dDeltaTime); // chama a mesma rotina no objeto-base

}