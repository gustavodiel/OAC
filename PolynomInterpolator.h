/**
   \file PolynomInterpolator.h
   \brief Descricao da classe PolynomInterpolator

   Esta classe tem por objetivo implementar uma interpola�ao Polynom entre atributos fornecidos

   Desenvolvido por Marlon Henry Schweigert<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _POLYNOMINTERPOLATOR_NOT_INCLUDED_
#define _POLYNOMINTERPOLATOR_NOT_INCLUDED_

#include "Interpolator.h"
#include "Matrix.h"
#include "PoseAttr.h"
#include "AttrVector3.h"

class PolynomInterpolator : public Interpolator
{
protected:
    Matrix* matrixX;
    Matrix* matrixY;
    Matrix* matrixZ;
    Matrix* matrixW;

    int iControlPoints;

    double dTmin, dTmax;

    double* pdCoefficientsX;
    double* pdCoefficientsY;
    double* pdCoefficientsZ;
    double* pdCoefficientsW;

private:
    double Px(double);
    double Py(double);
    double Pz(double);
    double Pw(double);

    PoseAttr::AttrName attrName;

public:
    PolynomInterpolator(AttrVector3::AttrName);
    PolynomInterpolator( const PolynomInterpolator & );
    PolynomInterpolator( PolynomInterpolator* );

    void Setup ();
    void OnLoop( double );
};

#endif
