#include "stdafx.h"
#include "Dama.h"

#include "Model.h"
#include "Headphone.h"


Dama::Dama()
{
	this->Initialize();
}

/*
\brief Construtor de copia para a classe Robot
Cria uma copia exata de um objeto Robot existente
\param clone Objeto  da classe Robot a ser clonado
*/
Dama::Dama(const Dama &clone) : Joint(clone)
{
	this->Initialize();
}


/**
\brief Construtor de copia para a classe Robot a partir de ponteiros
Cria uma copia exata de um objeto Robot existente
\param ptrClone Ponteiro para um objeto Robot a ser clonado
*/
Dama::Dama(Dama* ptrClone) : Joint(ptrClone)
{
	this->Initialize();
}


Dama::~Dama()
{
}


void Dama::Initialize() {
	Model *ptrBase = new Model("objs/rainha.obj", "textures/preto.jpg");
	ptrBase->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	ptrBase->setTranslate(glm::vec3(0, 0.0, 0));
	this->listOfEntities.push_back(ptrBase);

}