/**
   \file LinearInterpolator.h
   \brief Descricao da classe LinearInterpolator

   Esta classe tem por objetivo implementar uma interpolaçao linear entre atributos fornecidos

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _LINEARINTERPOLATOR_NOT_INCLUDED_
#define _LINEARINTERPOLATOR_NOT_INCLUDED_

#include "Interpolator.h"

class LinearInterpolator : public Interpolator
{
public:
    LinearInterpolator();
    LinearInterpolator( const LinearInterpolator & );
    LinearInterpolator( LinearInterpolator* );

    void OnLoop( double );
};

#endif
