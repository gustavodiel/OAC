/************************************************************************/
/* File: PolinomialInterpolator.h                                       */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Interpolator.h"

/**
\class PolinomialInterpolator
\brief Classe para calcular interpolacao seguindo diversas funcoes matematicas
*/
class PolinomialInterpolator : public Interpolator {
public:
    
	//!< tipos de interpoladores disponieis
    enum TipoLinearizacaoPolinomial {
        Cos = 0,					//!< funcao coseno
        Cubica,						//!< funcao cubica ( x^3 * (x * (6.0*x - 15.0f) + 10.0) )
        Quadrada,					//!< funcao quadrada ( x^2 )
        CubicaEQuadrada,			//!< juncao da cubica e quadrada ( j = x^2 -> ( j^3 * (j * (6.0*j - 15.0f) + 10.0) ) )
        Sin,						//!< funcao seno
        Smoothetep,					//!< funcao smoothstep ( x^2*(3 - 2*x) )
        Smootherstep,				//!< funcao de smootherstep ( x^2*(3 - 2*x)*(3 - 2*x) )
        Catmullrom,					//!< funcao de Catmull-Rom, mais informacoes em PolinomialInterpolator::CalculateCatmullrom
        SmoothstepDesacelerado,		//!< funcao de smoothstep so que desacelerado ( y = 1 - (1 - x) * (1 - x) * (1 - x) * (1 - x) -> y^2*(3 - 2*y) )
        Desacelerar,				//!< funcao desacelerada ( 1 - (1 - x) * (1 - x) )
        TESTE						//!< This is test
    };
    
    PolinomialInterpolator( TipoLinearizacaoPolinomial tipo = Cos );
    PolinomialInterpolator( const PolinomialInterpolator & );
    PolinomialInterpolator( PolinomialInterpolator* );
    
    void OnLoop( double );
    
protected:
    TipoLinearizacaoPolinomial tipo;	//!< cada interpolador precisa de um tipo para saber qual funcao deve utilizar

	/**
	\brief Calcula a funcao de Catmull-Rom para interpolacao, que cria uma curva com preparacao no comeco e no final avanca um pouco e volta. Para interpolacao, as variaveis p1 e p2 tem que ficar em 0 e 1 respectivamente
	\param t tempo indice entre 0 e 1 que seria a razao entre a primeira posicao e a proxima ( 0 = 100% da primeira e 1 = 100% da segunda )
	\param p0 coeficiente de como ele vai acelerar
	\param p1 numero onde a animacao deve comecar
	\param p2 numero onde a animacao deve terminar
	\param p3 coeficiente de como ele desacelerar
	\return double com o coeficiente que pode passar de 0 e 1 com o valor da animacao
	*/
	double CalculateCatmullrom(float t, float p0, float p1, float p2, float p3);
    
};
