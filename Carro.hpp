/************************************************************************/
/* File: Carro.hpp                                                      */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Entity.h"

/**
 \class Robot
 \brief Responsavel por construir um ator robÙ<br>
 
 \sa Object()
 */
class Carro: public Entity
{
public:
    Carro();
    Carro( const Carro & );
    Carro( Carro* );
    
    virtual void Initialize();
};
