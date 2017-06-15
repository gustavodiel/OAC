#pragma once

#include "Entity2D.h"

class Actor2D: public Entity2D
{
protected:
	class Animator * ptrAnimator; ///< ponteiro para o objeto animador de atributos associado a este ator

public:
	Actor2D(const Actor2D &);
	Actor2D(Actor2D*);
	Actor2D();
	~Actor2D();

	void setAnimator(class Animator *);
	/**
	\brief Retorna a referencia ao objeto animador associado a este objeto
	\return ponteiro para o objeto animador
	*/
	inline class Animator * getAnimator() { return this->ptrAnimator; }
	
	virtual void OnLoop(double);
};

