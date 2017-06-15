/************************************************************************/
/* File: House.h                                                        */
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
class House: public Entity
{
public:
    House();
    House( const House & );
    House( House* );

    virtual void Initialize();
};
