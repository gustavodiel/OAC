/************************************************************************/
/* File: PolinomialInterpolator.h                                       */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"
#include "PolinomialInterpolator.hpp"

/* Standard Includes */
#define _USE_MATH_DEFINES		//!< O Windows precisa desse define para definir as constantes matematicas
#include <cmath>
#include <stdio.h>
#include <typeinfo>
#include <string>

/* Utility Includes */
#include "PoseAttr.h"
#include "AttrVector3.h"


/**
 \brief Construtor para a classe LinearInterpolator
 */
PolinomialInterpolator::PolinomialInterpolator(TipoLinearizacaoPolinomial _tipo): Interpolator()
{
    this->tipo = _tipo;
}
/**
 \brief Construtor de clonagem para a classe LinearInterpolator
 Cria uma copia exata de um objeto entidade ja existente
 \param clone Objeto a ser clonado
 */
PolinomialInterpolator::PolinomialInterpolator( const PolinomialInterpolator& clone ): Interpolator( clone )
{
    this->tipo = clone.tipo;
}
/**
 \brief Construtor de clonagem para a classe LinearInterpolator a partir de ponteiros
 Cria uma copia exata de um objeto entidade ja existente
 \param ptrClone Ponteiro para o objeto a ser clonado
 */
PolinomialInterpolator::PolinomialInterpolator( PolinomialInterpolator* ptrClone ): Interpolator( ptrClone )
{
    this->tipo = ptrClone->tipo;
}

/**
\brief Calcula a funcao de Catmull-Rom para interpolacao, que cria uma curva com preparacao no comeco e no final avanca um pouco e volta. Para interpolacao, as variaveis p1 e p2 tem que ficar em 0 e 1 respectivamente
\param t tempo indice entre 0 e 1 que seria a razao entre a primeira posicao e a proxima ( 0 = 100% da primeira e 1 = 100% da segunda )
\param p0 coeficiente de como ele vai acelerar
\param p1 numero onde a animacao deve comecar
\param p2 numero onde a animacao deve terminar
\param p3 coeficiente de como ele desacelerar
\return double com o coeficiente que pode passar de 0 e 1 com o valor da animacao
*/
double PolinomialInterpolator::CalculateCatmullrom(float t, float p0, float p1, float p2, float p3)
{
    return 0.5f * (
                   (2 * p1) +
                   (-p0 + p2) * t +
                   (2 * p0 - 5 * p1 + 4 * p2 - p3) * t * t +
                   (-p0 + 3 * p1 - 3 * p2 + p3) * t * t * t
                   );
}

/**
 \brief Calcula o proximo valor da interpolaÁ„o
 \param dAnimationTime tempo acumulado deste o inicio do processo de animaÁ„o
 */
void PolinomialInterpolator::OnLoop( double dAnimationTime )
{
    for( unsigned int uiCounter = 0; uiCounter < this->listOfPoseAttr.size()-1; uiCounter++ )
    {
        // o tempo transcorrido na animaÁ„o est· dentro do intervalo entre poses ?
        if( dAnimationTime >= this->listOfPoseAttr[ uiCounter ]->getTime() && dAnimationTime <= this->listOfPoseAttr[ uiCounter+1 ]->getTime() )
        {
           
            float t = ( dAnimationTime - this->listOfPoseAttr[ uiCounter ]->getTime() ) / ( this->listOfPoseAttr[ uiCounter+1 ]->getTime() - this->listOfPoseAttr[ uiCounter ]->getTime());
            
            float t2 = t;
            
            glm::vec3 dir = (( AttrVector3* )this->listOfPoseAttr[ uiCounter + 1 ])->getValue() - (( AttrVector3* )this->listOfPoseAttr[ uiCounter ])->getValue();
            glm::vec3 dirNext = dir;
            if (this->listOfPoseAttr.size()-1 - uiCounter > 1){
                dirNext = (( AttrVector3* )this->listOfPoseAttr[ uiCounter + 2 ])->getValue() - (( AttrVector3* )this->listOfPoseAttr[ uiCounter + 1 ])->getValue();
                t2 = ( dAnimationTime - this->listOfPoseAttr[ uiCounter + 1 ]->getTime() ) / ( this->listOfPoseAttr[ uiCounter+2 ]->getTime() - this->listOfPoseAttr[ uiCounter ]->getTime());
            }
            float a;
            
            switch (this->tipo) {
                case Cos: // 1. Acelera/Desacelera rapido
                    a = (1.f-cos(t*M_PI))/3.f;
                    t = (t*(1.f-a)+a);
                    break;
                case Cubica: // 2. Mais suave
                    t = t*t*t * (t * (6.0f*t - 15.0f) + 10.0f);
                    break;
                case Quadrada: // 3. Acelera e nao desacelera ( quadrado ne e.e )
                    t = t * t;
                    break;
                case CubicaEQuadrada: // 4. Igual a 2, so que mais rapido
                    t = t * t;
                    t = t*t*t * (t * (6.0f*t - 15.0f) + 10.0f);
                    break;
                case Sin: // 6. Bem suave
                    t = sin(t * M_PI_2);
                    break;
                case Smoothetep: // 7. Smoothstep
                    t = t*t*(3.f - 2.f*t);
                    break;
                case Smootherstep: // 8. Smootherstep
                    t = t*t*(3.f - 2.f*t)*(3.0f - 2.0f*t);
                    break;
                case Catmullrom: // 9. Catmull-Rom
                    t = this->CalculateCatmullrom(t, 2, 0, 1, -1);
                    break;
                case SmoothstepDesacelerado: // 10. Desacelerar Com Smoothstep
                    t = 1.f - (1.f - t) * (1.f - t) * (1.f - t) * (1.f - t);
                    t = t*t*(3.f - 2.f*t);
                    break;
                case Desacelerar: // 11. Desacelerar
                    t = 1.f - (1.f - t) * (1.f - t);
                    break;
                case TESTE:
                    //t = atan(t * M_PI_2);
                    t = 1.f;
                    
            }			
            
            AttrVector3 * ptrTweenAttr = new AttrVector3(
                                                         (( AttrVector3* )this->listOfPoseAttr[ uiCounter ])->getValue() + dir * t,
                                                         0.0,
                                                         this->listOfPoseAttr[ uiCounter ]->getName() );
            ptrTweenAttr->updateParent( this->ptrOwner );
        }
    }
}
