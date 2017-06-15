/*

  Marlon Henry Schweigert © 2017 - UDESC
  Sistema de solução matricial pelo método de Gauss.

*/

#ifndef _MATRIX_NOT_INCLUDED_
#define _MATRIX_NOT_INCLUDED_

#include <stdlib.h>

class Matrix {
private:
  // mat -> MxN
  double** dMat;
  bool pivoted;
  double* dAnswer;

  unsigned int uiM;
  // M -> Colunas / Linhas


public:
  Matrix(unsigned int);
  ~Matrix();

  void print();
  void SetValue(int i, int j, double value);

  double* GaussMethod();
};

#endif
