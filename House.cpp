/**
   \file House.cpp
   \brief Implementacao dos metodos da classe House

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "stdafx.h"
#include "House.h"

#include "Model.h"

/**
  \brief Construtor padrao para a classe House
  Cria uma primitiva grafica composta
*/
House::House(): Entity()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe House
  Cria uma copia exata de um objeto House existente
  \param clone Objeto  da classe House a ser clonado
*/
House::House( const House &clone ): Entity( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe House a partir de ponteiros
  Cria uma copia exata de um objeto House existente
  \param ptrClone Ponteiro para um objeto House a ser clonado
*/
House::House( House* ptrClone ): Entity( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void House::Initialize()
{
	Model *ptrHouse = new Model("objs/box.obj", "textures/branco.jpg");
    ptrHouse->setScale( glm::vec3( 1.0f, 0.7f, 1.0f ));
    ptrHouse->setTranslate( glm::vec3( 0.0f, 0.35f, 0.0f ));
    this->listOfEntities.push_back( ptrHouse );
    
	Model *ptrRoof = new Model("objs/triangulo.obj", "textures/azul_c.jpg");
    ptrRoof->setScale( glm::vec3( 1.2f, 0.5f, 1.2f ));
    ptrRoof->setTranslate( glm::vec3( 0.0f, 0.9f, 0.0f ));
    this->listOfEntities.push_back( ptrRoof );
    
	Model *ptrRoof2 = new Model("objs/box.obj", "textures/preto.jpg");
    ptrRoof2->setScale( glm::vec3( 0.22f, 0.05f, 0.22f ) );
    ptrRoof2->setTranslate( glm::vec3( -0.2f, 1.2f, 0.2f ));
    this->listOfEntities.push_back( ptrRoof2 );
    
	Model *ptrRoof3 = new Model("objs/box.obj", "textures/preto.jpg");
    ptrRoof3->setScale( glm::vec3( 0.20f, 0.3f, 0.20f ) );
    ptrRoof3->setTranslate( glm::vec3( -0.2f, 1.05f, 0.2f ));
    this->listOfEntities.push_back( ptrRoof3 );

	Model *ptrDoor = new Model("objs/box.obj", "textures/vermelho.jpg");
    ptrDoor->setScale( glm::vec3( 0.2f, 0.4f, 0.2f ) );
    ptrDoor->setTranslate( glm::vec3( 0.0f, 0.2f, -0.42f ));
    this->listOfEntities.push_back( ptrDoor );
    
	Model *ptrWindow2 = new Model("objs/box.obj", "textures/azul_c.jpg");
    ptrWindow2->setScale( glm::vec3( 0.25f, 0.25f, 0.25f ) );
    ptrWindow2->setTranslate( glm::vec3( 0.42f, 0.4f, -0.0f ));
    this->listOfEntities.push_back( ptrWindow2 );
}


