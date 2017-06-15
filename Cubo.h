/************************************************************************/
/* File: Application.h                                                  */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Entity.h"
/**
   \class Robot
   \brief Responsavel por construir um ator robô<br>

   \sa Object()
*/
class Cubo: public Entity
{
public:
	Cubo();
	Cubo( const Cubo & );
	Cubo(Cubo* );

    virtual void Initialize();
};
