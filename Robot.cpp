/**
   \file Robot.cpp
   \brief Implementacao dos metodos da classe Robot

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "stdafx.h"
#include "Robot.h"
#include "Model.h"

/**
  \brief Construtor padrao para a classe Robot
  Cria uma primitiva grafica composta
*/
Robot::Robot(): Entity()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Robot
  Cria uma copia exata de um objeto Robot existente
  \param clone Objeto  da classe Robot a ser clonado
*/
Robot::Robot( const Robot &clone ): Entity( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Robot a partir de ponteiros
  Cria uma copia exata de um objeto Robot existente
  \param ptrClone Ponteiro para um objeto Robot a ser clonado
*/
Robot::Robot( Robot* ptrClone ): Entity( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void Robot::Initialize()
{
	Model *ptrBase = new Model("objs/box.obj", "textures/branco.jpg");
	ptrBase->setScale( glm::vec3( 0.35f, 0.1f, 0.35f ));
	this->listOfEntities.push_back( ptrBase );

	Model *ptrStem = new Model("objs/box.obj", "textures/branco.jpg");
	ptrStem->setScale( glm::vec3( 0.05f, 0.4f, 0.05f ) );
	ptrStem->setTranslate( glm::vec3( 0.0f, 0.2f, 0.0f ));
	this->listOfEntities.push_back( ptrStem );

	Model *ptrBody = new Model("objs/box.obj", "textures/vermelho.jpg");
	ptrBody->setScale( glm::vec3( 0.5f, 0.8f, 0.3f ) );
	ptrBody->setTranslate( glm::vec3( 0.0f, 0.7f, 0.0f ));
	this->listOfEntities.push_back( ptrBody );

	Model *ptrHead = new Model("objs/box.obj", "textures/branco.jpg");
	ptrHead->setScale( glm::vec3( 0.2f, 0.2f, 0.2f ) );
	ptrHead->setTranslate( glm::vec3( 0.0f, 1.2f, 0.0f ));
	this->listOfEntities.push_back( ptrHead );

	// braço esquerdo
	Model *ptrArm1 = new Model("objs/box.obj", "textures/branco.jpg");
	ptrArm1->setScale( glm::vec3( 0.1f, 0.5f, 0.1f ) );
	ptrArm1->setTranslate( glm::vec3( 0.3f, 0.8f, 0.0f ));
	this->listOfEntities.push_back( ptrArm1 );

	// braço direito
	ptrArm1 = new Model("objs/box.obj", "textures/branco.jpg");
	ptrArm1->setScale(glm::vec3(0.1f, 0.5f, 0.1f));
	ptrArm1->setTranslate(glm::vec3(-0.3f, 0.8f, 0.0f));
	this->listOfEntities.push_back(ptrArm1);
}
