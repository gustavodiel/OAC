/************************************************************************/
/* File: Tree.h                                                         */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/


#pragma once

#include "Entity.h"

/**
   \class Tree
   \brief Responsavel por construir um objeto do tipo arvore<br>

   \sa Object()
*/
class Tree: public Entity
{
public:
    Tree();
    Tree( const Tree & );
    Tree( Tree* );

	Model* tree;

    virtual void Initialize();
	virtual void OnLoop(double);
};
