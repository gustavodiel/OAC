#include "stdafx.h"
#include "Animator.h"

#include <stdlib.h>
#include "PoseAttr.h"

/**
\brief Construtor para a classe Animator
\param animType tipo de animação executada por este animador
*/
Animator::Animator(Animator::AnimationType animType) :
	ptrOwner(NULL), dAnimationTime(0.0), dAnimationDuration(0.0), animationType(animType)
{}
/**
\brief Construtor de clonagem para a classe Animator
Cria uma copia exata de um objeto entidade ja existente
\param clone Objeto a ser clonado
*/
Animator::Animator(const Animator& clone) : dAnimationTime(0.0)
{
	this->ptrOwner = clone.ptrOwner;
	this->animationType = clone.animationType;
	this->dAnimationDuration = clone.dAnimationDuration;
	this->listOfInterpolators = clone.listOfInterpolators;
}
/**
\brief Construtor de clonagem para a classe Animator a partir de ponteiros
Cria uma copia exata de um objeto entidade ja existente
\param ptrClone Ponteiro para o objeto a ser clonado
*/
Animator::Animator(Animator* ptrClone) : dAnimationTime(0.0)
{
	this->ptrOwner = ptrClone->ptrOwner;
	this->animationType = ptrClone->animationType;
	this->dAnimationDuration = ptrClone->dAnimationDuration;
	this->listOfInterpolators = ptrClone->listOfInterpolators;
}
/**
\brief Destrutor para os objetos dinamicos utilizados por esta classe
*/
Animator::~Animator()
{
	for (std::vector<Interpolator *>::iterator ptrInterp = this->listOfInterpolators.begin();
	ptrInterp != this->listOfInterpolators.end(); ptrInterp++)
		delete (*ptrInterp);
}
/**
\brief Associa este animador a um objeto-pai do tipo Entity
\param ptrOwner ponteiro para o objeto ao qual este animador sera associado
*/
void Animator::setParent(Entity* ptrOwner)
{
	this->ptrOwner = ptrOwner;

	for (vector<Interpolator *>::iterator ptrInterp = this->listOfInterpolators.begin();
	ptrInterp != this->listOfInterpolators.end(); ptrInterp++)
		(*ptrInterp)->setParent(this->ptrOwner);
}
/**
\brief Adiciona um novo interpolador a esta animação
\param ptrInterp pointeiro para o novo interpolador a ser adicionado a esta animação
*/
void Animator::addInterpolator(Interpolator * ptrInterp)
{
	if (ptrInterp)
	{
		for (unsigned int uiCounter = 0; uiCounter < ptrInterp->getNumberOfAttr(); uiCounter++)
			if (this->dAnimationDuration < ptrInterp->getAttribute(uiCounter)->getTime())
				this->dAnimationDuration = ptrInterp->getAttribute(uiCounter)->getTime();

		this->listOfInterpolators.push_back(ptrInterp);
	}
}
/**
\brief Executa o processo de animação
\param dDeltaTime tempo transcorrido deste a ultima chamada desta função
*/
void Animator::OnLoop(double dDeltaTime)
{
	if (bStopUpdating)
		return;

	this->dAnimationTime += dDeltaTime;

	for (vector<Interpolator *>::iterator itInterp = this->listOfInterpolators.begin();
	itInterp != this->listOfInterpolators.end(); itInterp++)
	{
		(*itInterp)->OnLoop(this->dAnimationTime);
	}

	if (this->dAnimationTime >= this->dAnimationDuration)
		if (this->animationType == Animator::LOOP)
			this->dAnimationTime = 0.0;
		else
			this->bStopUpdating = true;
}
