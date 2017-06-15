/************************************************************************/
/* File: Peao.h                                                         */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Joint.h"

class Peao :
	public Joint
{
public:
	Peao();	
	Peao(const Peao &);
	Peao(Peao*);
	~Peao();

	virtual void Initialize();

	inline class Headphone* getHeadphone() { return this->headphone; };

	inline Entity* getBase() { return this->base; };

protected:
	class Headphone* headphone;

	Entity* base;
};

