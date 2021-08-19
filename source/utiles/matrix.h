#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>

using namespace std;

class Matrix
{
public:
    ~Matrix();
    Matrix(Matrix *);
    Matrix(float, int , int );
  //    Matrix(float a[], int , int );
    int columnas();
    int  filas();
    void num(float , int , int);
    float num(int, int);
    Matrix * concatenar(Matrix *,int);
    float filaVector(int, Matrix *);
    float * getArreglo();
 //   Matrix* operator * (Matrix *);
    // Matrix*  productoEE (Matrix *);
  //   Matrix* operator * (float);
  //  Matrix* operator + (Matrix *);
    Matrix * transpuesta();
    Matrix ( int, int );
    Matrix(int x, int y, float a[]);
    void mostrar();
     void mostrar(string );
    float floatRandom();
    Matrix *  instMatrix(int , Matrix * );

    Matrix *operacionEE(char op, Matrix *mat);
  //  Matrix *operator -(float num);
    Matrix *productoVectorial(Matrix *mat);
    Matrix *resta(float num);
    Matrix *multiplicacionXescalar(float valor);
private:
    float *matrix;
    int cantFilas =0;
    int cantColumnas =0;
};

#endif // MATRIX_H
