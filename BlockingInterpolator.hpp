/**
 \file LinearInterpolator.h
 \brief Descricao da classe LinearInterpolator
 
 Esta classe tem por objetivo implementar uma interpolaÁao linear entre atributos fornecidos
 
 Desenvolvido por Rogerio Eduardo da Silva<br>
 MarÁo, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
 */
#ifndef _BLOCKINGINTERPOLATOR_NOT_INCLUDED_
#define _BLOCKINGINTERPOLATOR_NOT_INCLUDED_

#include "Interpolator.h"

class BlockingInterpolator : public Interpolator
{
protected:
    double dPrecision; ///< precisao para aproximar doubles
    
public:
    BlockingInterpolator();
    BlockingInterpolator( const BlockingInterpolator & );
    BlockingInterpolator( BlockingInterpolator* );
    
    void OnLoop( double );
    
    void setPrecision(double);
};

#endif //_BLOCKINGINTERPOLATOR_NOT_INCLUDED_
