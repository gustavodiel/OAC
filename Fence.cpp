/**
   \file Fence.cpp
   \brief Implementacao dos metodos da classe Fence

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "stdafx.h"
#include "Fence.h"
#include "Model.h"

/**
  \brief Construtor padrao para a classe Fence
  Cria uma primitiva grafica composta
*/
Fence::Fence(): Entity()
{
}

/*
  \brief Construtor de copia para a classe Fence
  Cria uma copia exata de um objeto Fence existente
  \param clone Objeto  da classe Fence a ser clonado
*/
Fence::Fence( const Fence &clone ): Entity( clone )
{
}


/**
  \brief Construtor de copia para a classe Fence a partir de ponteiros
  Cria uma copia exata de um objeto Fence existente
  \param ptrClone Ponteiro para um objeto Fence a ser clonado
*/
Fence::Fence( Fence* ptrClone ): Entity( ptrClone )
{
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void Fence::Initialize(std::vector<Entity*>*arvores)
{
	int size = 10;
	for (int i = 0; i < size; ++i) {
		Model *ptrFence1 = new Model("objs/box.obj", "textures/marrom_e.jpg");
		ptrFence1->setScale(glm::vec3(0.1f, 1.0f, 0.05f));
		ptrFence1->setTranslate(glm::vec3(i * 0.4f, 0.5f, 0.0f));
		this->listOfEntities.push_back(ptrFence1);
		arvores->push_back(ptrFence1);
	}

	Model *ptrFence7 = new Model("objs/box.obj", "textures/marrom_e.jpg");
	ptrFence7->setScale(glm::vec3(size * 0.4f, 0.1f, 0.05f));
	ptrFence7->setTranslate(glm::vec3(size * 0.2f, 0.4f, 0.0f));
	this->listOfEntities.push_back(ptrFence7);

	Model *ptrFence8 = new Model("objs/box.obj", "textures/marrom_e.jpg");
	ptrFence8->setScale(glm::vec3(size * 0.4f, 0.1f, 0.05f));
	ptrFence8->setTranslate(glm::vec3(size * 0.2f, 0.6f, 0.0f));
	this->listOfEntities.push_back(ptrFence8);


}
