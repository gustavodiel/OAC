/************************************************************************/
/* File: Fence.h                                                        */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Entity.h"
#include <vector>

/**
   \class Fence
   \brief Responsavel por construir um objeto do tipo cerca<br>

   \sa Object()
*/
class Fence: public Entity
{
public:
    Fence();
    Fence( const Fence & );
    Fence( Fence* );

    virtual void Initialize(std::vector<Entity*>*arvores);
};
