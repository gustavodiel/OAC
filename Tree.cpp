/**
   \file Tree.cpp
   \brief Implementacao dos metodos da classe Tree

   Desenvolvido por Gustavo Diel<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "stdafx.h"
#include "Model.h"

#include "Tree.h"

#include "Application.h"
#include "Constants.h"
#include "ParticleSystem.h"

/**
  \brief Construtor padrao para a classe Tree
  Cria uma primitiva grafica composta
*/
Tree::Tree(): Entity()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Tree
  Cria uma copia exata de um objeto Tree existente
  \param clone Objeto  da classe Tree a ser clonado
*/
Tree::Tree( const Tree &clone ): Entity( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Tree a partir de ponteiros
  Cria uma copia exata de um objeto Tree existente
  \param ptrClone Ponteiro para um objeto Tree a ser clonado
*/
Tree::Tree( Tree* ptrClone ): Entity( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void Tree::Initialize()
{
	tree = new Model("objs/tree.obj", "textures/canterlot_tree.png");
	tree->setScale( glm::vec3( 0.005f, 0.005f, 0.005f));
	tree->setRotate(vec3(0, rand() % 360, 0));
	tree->setShearable(true);
	this->listOfEntities.push_back(tree);

	ParticleSystem* ps = new ParticleSystem("textures/folha.png", 40, vec3(0,0,0), vec3(0.0f, 0.0f, 0.0f));
	ptrApp->AddParticleSystem(ps);

	ps->SetEmitter(this);

	ps->SetBirthFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		p->fLife = 20.0f;
		float radius = rand() % 2000 / 1000.0f - 1.0f;
		float dir1 = radians(float(rand() % 360));
		float dir2 = radians(float(rand() % 360));

		float xOff = sin(dir1) * cos(dir2) * radius;
		float yOff = sin(dir1) * sin(dir2) * radius;
		float zOff = cos(dir1) * radius;

		p->vPosition = ps->GetEmitter()->GetWorldPosition() + vec3(zOff, xOff, yOff);
		p->vPosition.y += 1.5;

		float spread = 1.5f;

		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);
		p->vSpeed = vec3(0);

		p->cR = rand() % 50;
		p->cG = 255;
		p->cB = 0;
		p->cA = 255;

		p->fSize = 0.05f;
	});

	ps->SetDeathFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		p->fCameraDist = -1.0f;
	});

	ps->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
		p->vSpeed += glm::vec3(0.5f, 0, 0.0f) * (float)dDeltaTime * 0.5f;
		p->vPosition += p->vSpeed * (float)dDeltaTime;

		p->vPosition.y += ((sin(ptrApp->GetApplicationTime() + p->iIndex) - 0.5) / 5) * dDeltaTime;

		if (p->vPosition.y < 0.0f) {
			p->vSpeed.y *= -2.0f * p->fSize;
			p->vPosition.y = 0.0f;
		}
	});

}

void Tree::OnLoop(double dDeltaTime) {
	this->tree->setShear(sin(ptrApp->GetApplicationTime() * 0.5) * 0.05, 0);
}

