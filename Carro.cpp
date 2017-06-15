//
//  Carro.cpp
//  OACO 3
//
//  Created by Gustavo Diel on 11/04/17.
//  Copyright © 2017 Gustavo Diel. All rights reserved.
//
#include "stdafx.h"
#include "Carro.hpp"

#include "Model.h"
#include "ParticleSystem.h"

#include "Constants.h"
#include "Application.h"

#include <glm\gtx\color_space.hpp>
#include "Utilities.hpp"

/**
 \brief Construtor padrao para a classe Robot
 Cria uma primitiva grafica composta
 */
Carro::Carro(): Entity()
{
    this->Initialize();
}

/*
 \brief Construtor de copia para a classe Robot
 Cria uma copia exata de um objeto Robot existente
 \param clone Objeto  da classe Robot a ser clonado
 */
Carro::Carro( const Carro &clone ): Entity( clone )
{
    this->Initialize();
}


/**
 \brief Construtor de copia para a classe Robot a partir de ponteiros
 Cria uma copia exata de um objeto Robot existente
 \param ptrClone Ponteiro para um objeto Robot a ser clonado
 */
Carro::Carro( Carro* ptrClone ): Entity( ptrClone )
{
    this->Initialize();
}

/**
 \brief Rotina responsavel pela construÁ„o do objeto
 */
void Carro::Initialize()
{

	/************************************************************************************/
	/*                                BASE                                              */
	/************************************************************************************/

	Model *ptrBase = new Model("objs/box.obj", "textures/vermelho.jpg");
    ptrBase->setScale( glm::vec3( 1.5f, 0.5f, 1.0f ));
    ptrBase->setTranslate( glm::vec3(0, 0.5, 0));
	this->AddEntity(ptrBase);

	ParticleSystem* ps = new ParticleSystem("textures/cloud2.png", 5000);
	ptrApp->AddParticleSystem(ps);

	ps->SetEmitter(ptrBase);

	ps->SetBirthFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		if (ptrApp->GetApplicationTime() > 20.5f) {
			return;
		}
		p->fLife = 1.0f;
		p->fTotalLife = p->fLife;
		p->vPosition = ps->GetEmitter()->GetWorldPosition() + vec3(-0.5, -0.2, 0);
		float spread = 0.55f;

		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);
		p->vSpeed = vec3(-1.0f, 0.0f, 0.0f) + randomdir*spread;

		p->cR = 200;
		p->cG = 200;
		p->cB = 200;

		p->cA = 100;

		p->fSize = 0.05f;
	});

	ps->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		p->vSpeed += glm::vec3(0.0f, 1.5f, 0.0f) * (float)(dDeltaTime * 0.5f * (rand() % 10000) / 1000.0f);
		p->vPosition += p->vSpeed * (float)dDeltaTime;

		p->cA = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 100.0f, 0.0f);

		p->fSize = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 0.05f, 0.55f);

	});

	/************************************************************************************/
	/*                                RODAS                                             */
	/************************************************************************************/
	for (auto a : { glm::vec3(0.5f, 0.3f, -0.5f), glm::vec3(-0.5f, 0.3f, -0.5f), glm::vec3(0.5f, 0.3f, 0.5f), glm::vec3(-0.5f, 0.3f, 0.5f) }) {
		Model * ptrRoda = new Model("objs/circle.obj", "textures/branco.jpg");
		ptrRoda->setScale(glm::vec3(0.1f, 0.1f, 0.05f));
		ptrRoda->setTranslate(a);
		this->AddEntity(ptrRoda);

		ParticleSystem* psRodaTraseira = new ParticleSystem("textures/cloud2.png", 1000);
		ptrApp->AddParticleSystem(psRodaTraseira);

		//ps->GetEmitter()->setAnimator(ptrPartAnim);

		psRodaTraseira->SetEmitter(ptrRoda);

		psRodaTraseira->SetBirthFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
			if (ptrApp->GetApplicationTime() > 20.2f) {
				return;
			}
			p->fLife = 0.05f;
			p->fTotalLife = p->fLife;
			p->vPosition = ps->GetEmitter()->GetWorldPosition() + vec3(0, -0.2, 0);
			float spread = 0.95f;

			glm::vec3 randomdir = glm::vec3(
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
			);
			p->vSpeed = vec3(-1.0f, 0.0f, 0.0f) + randomdir*spread;

			p->cR = 139;
			p->cG = 69;
			p->cB = 19;

			p->cA = 100;

			p->fSize = 0.05f;
		});

		psRodaTraseira->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
			p->vSpeed += glm::vec3(0.0f, 0.7f, 0.0f) * (float)(dDeltaTime * 0.5f);
			p->vPosition += p->vSpeed * (float)dDeltaTime;

			p->cA = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 100.0f, 0.0f);

			p->fSize = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 0.001f, 0.55f);

		});
	}

  /*  
	Model *ptrRoda1 = new Model("objs/circle.obj", "textures/branco.jpg");
    ptrStem->setScale( glm::vec3( 0.1f, 0.1f, 0.05f ) );
    ptrStem->setTranslate( glm::vec3( 0.5f, 0.3f, -0.5f ));
    this->listOfEntities.push_back( ptrStem );

	Model * ptrRoda2 = new Model("objs/circle.obj", "textures/branco.jpg");
	ptrStem->setScale( glm::vec3( 0.1f, 0.1f, 0.05f ) );
    ptrStem->setTranslate( glm::vec3( -0.5f, 0.3f, -0.5f ));
    this->listOfEntities.push_back( ptrStem );

	ParticleSystem* psRodaTraseira = new ParticleSystem("textures/cloud2.png", 5000);
	ptrApp->AddParticleSystem(psRodaTraseira);

	//ps->GetEmitter()->setAnimator(ptrPartAnim);

	psRodaTraseira->SetEmitter(ptrStem);

	psRodaTraseira->SetBirthFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		if (ptrApp->GetApplicationTime() > 20.2f) {
			return;
		}
		p->fLife = 1.0f;
		p->fTotalLife = p->fLife;
		p->vPosition = ps->GetEmitter()->GetWorldPosition() + vec3(-0.5, -0.2, 0);
		float spread = 0.55f;

		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);
		p->vSpeed = vec3(-1.0f, 0.0f, 0.0f) + randomdir*spread;

		p->cR = 200;
		p->cG = 50;
		p->cB = 0;

		p->cA = 100;

		p->fSize = 0.05f;
	});

	psRodaTraseira->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		p->vSpeed += glm::vec3(0.0f, 1.5f, 0.0f) * (float)(dDeltaTime * 0.5f * (rand() % 10000) / 1000.0f);
		p->vPosition += p->vSpeed * (float)dDeltaTime;

		p->cA = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 100.0f, 0.0f);

		p->fSize = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 0.05f, 0.55f);

	});
    
    
	Model * ptrRoda3 = new Model("objs/circle.obj", "textures/branco.jpg");
    ptrStem->setScale( glm::vec3( 0.1f, 0.1f, 0.05f ) );
    ptrStem->setTranslate( glm::vec3( 0.5f, 0.3f, 0.5f ));
    this->listOfEntities.push_back( ptrStem );
    
	Model * ptrRoda4 = new Model("objs/circle.obj", "textures/branco.jpg");
    ptrStem->setScale( glm::vec3( 0.1f, 0.1f, 0.05f ) );
    ptrStem->setTranslate( glm::vec3( -0.5f, 0.3f, 0.5f ));
	this->AddEntity(ptrStem);


	*/
}
