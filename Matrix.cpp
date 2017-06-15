// Source from http://www.codewithc.com/c-program-for-gauss-jordan-method/
#include "stdafx.h"
#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>

Matrix::Matrix(unsigned int M): pivoted(false)
{
  this->uiM = M;
  this->dMat = (double**)malloc(sizeof(double*)*(this->uiM+3));
  for(int i = 0; i<uiM + 3; i++){
    this->dMat[i] = (double*)malloc(sizeof(double)*(this->uiM+3));
    for(int j = 0; j < uiM + 3; j++){
      this->dMat[i][j] = 0.0;
    }
  }

  this->dAnswer = (double*)malloc(sizeof(double)*(this->uiM+3));

}

void Matrix::SetValue(int i, int j, double value){
  this->dMat[i][j] = value;
}

void Matrix::print(){
  for(int i = 1; i <= uiM; i++){
    for(int j = 1; j <= uiM +1; j++){
      printf("%lf ", dMat[i][j]);
    }
    printf("\n");
  }
}

Matrix::~Matrix()
{
  for(unsigned int i = 0; i < this->uiM+3; i++){
    free(this->dMat[i]);
  }
  free(this->dMat);
  free(this->dAnswer);
}

double* Matrix::GaussMethod()
{

  if(pivoted){
    goto resp;
  }

  double c;

  for( int j = 1; j <= this->uiM; j++){
    for(int i = 1; i <= this->uiM; i++){
      if(i!=j){
        c=this->dMat[i][j]/this->dMat[j][j];
        for(int k = 1; k <= this->uiM+1; k++){
          this->dMat[i][k] = this->dMat[i][k]-c*this->dMat[j][k];
        }
      }
    }
  }

  for(int i = 1; i <= this->uiM; i++){
    this->dAnswer[i-1] = this->dMat[i][this->uiM+1]/this->dMat[i][i];
    // printf("%lf\n", this->dAnswer[i]);
  }
  this->pivoted = true;
  resp:
  return this->dAnswer;
}
