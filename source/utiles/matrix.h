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
    int columnas();
    int  filas();
    void num(float , int , int);
    float num(int, int);
    float * getArreglo();
    Matrix ( int, int );
    void mostrar();
    void mostrar(string );
    float floatRandom();
private:
    float *matrix;
    int cantFilas =0;
    int cantColumnas =0;
};

#endif // MATRIX_H
