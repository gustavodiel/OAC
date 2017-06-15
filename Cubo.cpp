/**
   \file Cubo.cpp
   \brief Implementacao dos metodos da classe Cubo

   Desenvolvido por Gustavo Diel<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "stdafx.h"
#include "Cubo.h"

#include "Model.h"

/**
  \brief Construtor padrao para a classe Robot
  Cria uma primitiva grafica composta
*/
Cubo::Cubo(): Entity()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Robot
  Cria uma copia exata de um objeto Robot existente
  \param clone Objeto  da classe Robot a ser clonado
*/
Cubo::Cubo( const Cubo &clone ): Entity( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Robot a partir de ponteiros
  Cria uma copia exata de um objeto Robot existente
  \param ptrClone Ponteiro para um objeto Robot a ser clonado
*/
Cubo::Cubo(Cubo* ptrClone ): Entity( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void Cubo::Initialize()
{
	Model *ptrBase = new Model("objs/box.obj", "textures/azul_c.jpg");
	ptrBase->setScale( glm::vec3( 1, 1, 1 ));

	ptrBase->getMaterial()->SetSpecularColor(10.0, 10.0, 10.0);

	this->listOfEntities.push_back( ptrBase );
}
