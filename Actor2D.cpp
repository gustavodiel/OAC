#include "stdafx.h"
#include "Actor2D.h"

#include "Animator.h"

/**
\brief Construtor para a classe Actor2D
Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
em escala canonica.
*/
Actor2D::Actor2D() : ptrAnimator(NULL)
{
}

/**
\brief Construtor de clonagem para a classe Actor2D
Cria uma copia exata de um objeto entidade ja existente
\param clone Objeto a ser clonado
*/
Actor2D::Actor2D(const Actor2D& clone)
{
	this->ptrAnimator = new Animator(clone.ptrAnimator);
}
/**
\brief Construtor de clonagem para a classe Actor2D a partir de ponteiros
Cria uma copia exata de um objeto entidade ja existente
\param ptrClone Ponteiro para o objeto a ser clonado
*/
Actor2D::Actor2D(Actor2D* ptrClone)
{
	this->ptrAnimator = new Animator(ptrClone->ptrAnimator);
}
/**
\brief Desaloca os objetos dinamicos desta classe
*/
Actor2D::~Actor2D()
{

	if (this->ptrAnimator)
		delete this->ptrAnimator;
	this->ptrAnimator = NULL;   // as vezes a operaçao de delete mantem lixo no ponteiro
}
/**
\brief Associa um objeto animador com este ator
\param ptrAnimator ponteiro do objeto animador a ser associado
*/
void Actor2D::setAnimator(Animator* ptrAnimator)
{
	if (ptrAnimator)
	{
		this->ptrAnimator = ptrAnimator;
		this->ptrAnimator->setParent(this);
	}
}
/**
\brief Executa o processo de animação
\param dDeltaTime tempo transcorrido deste a ultima chamada desta função
*/
void Actor2D::OnLoop(double dDeltaTime)
{
	if (this->ptrAnimator) {
		this->ptrAnimator->OnLoop(dDeltaTime);
	}

}

