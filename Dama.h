/************************************************************************/
/* File: Dama.h                                                         */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Joint.h"

class Dama :
	public Joint
{
public:
	Dama();
	Dama(const Dama &);
	Dama(Dama*);
	~Dama();

	virtual void Initialize();

protected:
};

