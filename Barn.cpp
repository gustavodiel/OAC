/**
 \file House.cpp
 \brief Implementacao dos metodos da classe House
 
 Desenvolvido por Rogerio Eduardo da Silva<br>
 MarÁo, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
 */
#include "stdafx.h"
#include "Model.h"
#include "Barn.hpp"
#include "ParticleSystem.h"
#include "Constants.h"
#include "Application.h"
#include "Utilities.hpp"

/**
 \brief Construtor padrao para a classe House
 Cria uma primitiva grafica composta
 */
Barn::Barn(): Entity()
{
}

/*
 \brief Construtor de copia para a classe House
 Cria uma copia exata de um objeto House existente
 \param clone Objeto  da classe House a ser clonado
 */
Barn::Barn( const Barn &clone ): Entity( clone )
{
}


/**
 \brief Construtor de copia para a classe House a partir de ponteiros
 Cria uma copia exata de um objeto House existente
 \param ptrClone Ponteiro para um objeto House a ser clonado
 */
Barn::Barn( Barn* ptrClone ): Entity( ptrClone )
{
}

/**
 \brief Rotina responsavel pela construÁ„o do objeto
 */
void Barn::Initialize()
{
 //   Model *ptrHouse = new Model("objs/barn.obj", "textures/wood 2.jpg");
 //   ptrHouse->setScale( glm::vec3( 0.5f, 0.5f, 0.5f ));
 //   ptrHouse->setTranslate(glm::vec3( 0.0f, 0.35f, 0.0f ));
	//ptrHouse->setRotate(vec3(0, 180, 0));

	Model* ptrHouse = new Model("objs/teste.blend", "textures/wood 2.jpg");
	ptrHouse->setScale(vec3(1.5f, 1.9f, 0.925f));
	ptrHouse->setRotate(vec3(-90, 0, 0));
	ptrHouse->setTranslate(vec3(0, 1.0, 0));
	ptrHouse->setName("Barn");
	this->AddEntity(ptrHouse);
	//this->listOfEntities.push_back(ptrHouse);

	ptrHouse->setStatic(true);
	ptrHouse->ActivatePhysics(Entity::BOX);


	Model* ptrVarau = new Model("objs/varau.obj", "textures/varau.jpg");
	ptrVarau->setScale(vec3(0.755f, 1.32f, 1.0f));
	ptrVarau->setRotate(vec3(0, 90, 0));
	ptrVarau->setTranslate(vec3(4.6, 0, 2.8));
	this->listOfEntities.push_back(ptrVarau);
 
	ParticleSystem* psRodaTraseira = new ParticleSystem("textures/cloud2.png", 100000);
	ptrApp->AddParticleSystem(psRodaTraseira);

	//ps->GetEmitter()->setAnimator(ptrPartAnim);

	psRodaTraseira->SetEmitter(ptrHouse);

	psRodaTraseira->SetBirthFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		p->fLife = 2.f;
		p->fTotalLife = p->fLife;
		p->vPosition = ps->GetEmitter()->GetWorldPosition() + vec3(1.2, 1.9, 1.2);
		float spread = 0.55f;

		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);
		p->vSpeed = randomdir*spread;

		p->cR = 200;
		p->cG = 200;
		p->cB = 200;

		p->cA = 150;

		p->fSize = 0.5f;
	});

	psRodaTraseira->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		p->vSpeed += glm::vec3(1.5f, 3.f, 0.0f) * (float)(dDeltaTime * 0.5f);
		p->vPosition += p->vSpeed * (float)dDeltaTime;

		p->cA = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 100.0f, 0.0f);

		p->fSize = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 0.001f, 0.55f);

	});
}


