/**
 \file LinearInterpolator.cpp
 \brief Implementacao dos metodos da classe LinearInterpolator
 
 Desenvolvido por Rogerio Eduardo da Silva<br>
 MarÁo, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
 */
#include "stdafx.h"
#include "BlockingInterpolator.hpp"

#include "PoseAttr.h"
#include "AttrVector3.h"

#include <stdio.h>
#include <typeinfo>
#include <string>

/**
 \brief Construtor para a classe LinearInterpolator
 */
BlockingInterpolator::BlockingInterpolator(): Interpolator(), dPrecision(0.0001)
{}
/**
 \brief Construtor de clonagem para a classe LinearInterpolator
 Cria uma copia exata de um objeto entidade ja existente
 \param clone Objeto a ser clonado
 */
BlockingInterpolator::BlockingInterpolator( const BlockingInterpolator& clone ): Interpolator( clone )
{

    this->dPrecision = clone.dPrecision;

}
/**
 \brief Construtor de clonagem para a classe LinearInterpolator a partir de ponteiros
 Cria uma copia exata de um objeto entidade ja existente
 \param ptrClone Ponteiro para o objeto a ser clonado
 */
BlockingInterpolator::BlockingInterpolator( BlockingInterpolator* ptrClone ): Interpolator( ptrClone )
{

    this->dPrecision = ptrClone->dPrecision;
    
}

void BlockingInterpolator::setPrecision(double _dPrecision){
    this->dPrecision = _dPrecision;
}

/**
 \brief Calcula o proximo valor da interpolaÁ„o
 \param dAnimationTime tempo acumulado deste o inicio do processo de animaÁ„o
 */
void BlockingInterpolator::OnLoop( double dAnimationTime )
{
    for( unsigned int uiCounter = 0; uiCounter < this->listOfPoseAttr.size(); uiCounter++ )
    {
        // o tempo transcorrido na animaÁ„o est· dentro do intervalo entre poses ?
        if( this->listOfPoseAttr[ uiCounter ]->getTime() - dAnimationTime <= this->dPrecision )
        {
            AttrVector3 * ptrTweenAttr = new AttrVector3(
                                                         (( AttrVector3* )this->listOfPoseAttr[ uiCounter ])->getValue(),
                                                         0.0,
                                                         this->listOfPoseAttr[ uiCounter ]->getName() );
            ptrTweenAttr->updateParent( this->ptrOwner );
        }
    }
}
