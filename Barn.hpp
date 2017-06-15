/************************************************************************/
/* File: Barn.hpp                                                       */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/


#pragma once

#include "Entity.h"

/**
 \class House
 \brief Responsavel por construir um objeto do tipo casa<br>
 
 \sa Object()
 */
class Barn: public Entity
{
public:
    Barn();
    Barn( const Barn & );
    Barn( Barn* );
    
    virtual void Initialize();
};