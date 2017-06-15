/************************************************************************/
/* File: Headphones.h                                                   */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Joint.h"

class Headphone :
	public Joint
{
public:
	Headphone();
	~Headphone();

	virtual void Initialize();

};

