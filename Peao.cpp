#include "stdafx.h"
#include "Peao.h"

#include "Model.h"
#include "Headphone.h"

#include "Constants.h"
#include "Application.h"



Peao::Peao()
{
	this->Initialize();
}

/*
\brief Construtor de copia para a classe Robot
Cria uma copia exata de um objeto Robot existente
\param clone Objeto  da classe Robot a ser clonado
*/
Peao::Peao(const Peao &clone) : Joint(clone)
{
	this->Initialize();
}


/**
\brief Construtor de copia para a classe Robot a partir de ponteiros
Cria uma copia exata de um objeto Robot existente
\param ptrClone Ponteiro para um objeto Robot a ser clonado
*/
Peao::Peao(Peao* ptrClone) : Joint(ptrClone)
{
	this->Initialize();
}


Peao::~Peao()
{
}


void Peao::Initialize() {
	base = new Model("objs/peaoRigid.obj", "textures/branco.jpg");
	base->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	base->setTranslate(vec3(0, 1.21, 0));
	this->AddEntity(base);

	ptrApp->AddTimerFunction([this](double deltaTime) {
		this->getBase()->setTranslate(this->getTranslate());
		this->getBase()->setScale(this->getScale());
		this->DelEntity(this->getBase());

		ptrApp->AddEntity(this->getBase());

		this->getBase()->setMass(10.0f);
		this->getBase()->ActivatePhysics(Entity::BOX);

		this->getBase()->getRigidBody()->setLinearVelocity(btVector3(10, 2, 0));
		this->getBase()->getRigidBody()->setAngularVelocity(btVector3(0, 0, 50));

	}, 20.0f);

	headphone = new Headphone();
	headphone->setScale(vec3(0.08f, 0.05, 0.08f));
	headphone->setTranslate(vec3(0, 0.65, 0));
	headphone->Initialize();
	this->Attach(headphone);

	ptrApp->AddTimerFunction([this](double deltaTime) {
		//this->getHeadphone()->setTranslate(this->getTranslate() + this->getHeadphone()->getTranslate());
		this->DelEntity(this->getHeadphone());

		ptrApp->AddEntity(this->getHeadphone());

		this->getHeadphone()->setMass(2.0f);
		this->getHeadphone()->ActivatePhysics(Entity::BOX);

		this->getHeadphone()->getRigidBody()->setLinearVelocity(btVector3(10, 2, 0));
		this->getHeadphone()->getRigidBody()->setAngularVelocity(btVector3(10, 2, 0));

	}, 20.0f);

}
