/**
   \file PolynomInterpolator.cpp
   \brief Implementacao dos metodos da classe PolynomInterpolator

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "stdafx.h"
#include "PolynomInterpolator.h"
#include "PoseAttr.h"
#include "AttrVector3.h"
#include "Matrix.h"

#include <stdio.h>
#include <typeinfo>
#include <string>
#include <math.h>

/**
  \brief Construtor para a classe PolynomInterpolator
*/
PolynomInterpolator::PolynomInterpolator(PoseAttr::AttrName attr): Interpolator()
{
  this->dTmin = 0;
  this->dTmax = 0;
  this->attrName = attr;
}


double PolynomInterpolator::Px(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsX[j];
  }
  return r;
}


double PolynomInterpolator::Py(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsY[j];
  }
  return r;
}


double PolynomInterpolator::Pz(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsZ[j];
  }
  return r;
}


double PolynomInterpolator::Pw(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsW[j];
  }
  return r;
}
/**
  \brief Calcula os valores necessários para a interpolação
*/
void PolynomInterpolator::Setup()
{

  double aux;

  // Número de pontos
  this->iControlPoints = this->listOfPoseAttr.size();

  this->matrixX = new Matrix(this->iControlPoints);
  this->matrixY = new Matrix(this->iControlPoints);
  this->matrixZ = new Matrix(this->iControlPoints);
  this->matrixW = new Matrix(this->iControlPoints);

  // Resolvendo para X
  for(int i = 0; i < iControlPoints; i++){
    matrixX->SetValue(i+1,iControlPoints+1,((AttrVector3*)this->listOfPoseAttr[i])->getValue().x);
    aux = ((AttrVector3*)this->listOfPoseAttr[i])->getTime();
    // Pega o maior e menor valor
    if(aux <= dTmin)
      dTmin = aux;

    if(aux >= dTmax)
      dTmax = aux;
    for(int j = 0; j < iControlPoints; j++){
      matrixX->SetValue(i+1,j+1, pow(aux,j));
    }
  }


  pdCoefficientsX = matrixX->GaussMethod();



  // Resolvendo para Y
  for(int i = 0; i < iControlPoints; i++){
    matrixY->SetValue(i+1,iControlPoints+1,((AttrVector3*)this->listOfPoseAttr[i])->getValue().y);
    aux = ((AttrVector3*)this->listOfPoseAttr[i])->getTime();
    for(int j = 0; j < iControlPoints; j++){
      matrixY->SetValue(i+1,j+1, pow(aux,j));
    }
  }

  pdCoefficientsY = matrixY->GaussMethod();


  // Resolvendo para Z
  for(int i = 0; i < iControlPoints; i++){
    matrixZ->SetValue(i+1,iControlPoints+1,((AttrVector3*)this->listOfPoseAttr[i])->getValue().z);
    aux = ((AttrVector3*)this->listOfPoseAttr[i])->getTime();
    for(int j = 0; j < iControlPoints; j++){
      matrixZ->SetValue(i+1,j+1, pow(aux,j));
    }
  }

  pdCoefficientsZ = matrixZ->GaussMethod();

}
/**
   \brief Calcula o proximo valor da interpola��o
   \param dAnimationTime tempo acumulado deste o inicio do processo de anima��o
*/
void PolynomInterpolator::OnLoop( double dAnimationTime )
{
  if(dAnimationTime >= dTmax && dAnimationTime <= dAnimationTime)
    return;



  AttrVector3 * ptrTweenAttr = new AttrVector3 (
    glm::vec3 (
      Px(dAnimationTime),
      Py(dAnimationTime),
      Pz(dAnimationTime)
    ),
      0.0
     ,
     attrName
    );

  ptrTweenAttr->updateParent( this->ptrOwner );
  delete ptrTweenAttr;

}
