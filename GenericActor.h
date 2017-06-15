/************************************************************************/
/* File: GenericActor.h                                                 */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Entity.h"

class GenericActor : public Entity
{
public:
	GenericActor(const char*, const char*);
	~GenericActor();
};

