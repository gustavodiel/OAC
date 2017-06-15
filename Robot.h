/************************************************************************/
/* File: Robot.h                                                        */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Entity.h"
/**
   \class Robot
   \brief Responsavel por construir um ator robô<br>

   \sa Actor()
*/
class Robot: public Entity
{
public:
    Robot();
    Robot( const Robot & );
    Robot( Robot* );

    virtual void Initialize();
};
