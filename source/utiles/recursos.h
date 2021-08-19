#ifndef RECURSOS_H
#define RECURSOS_H
#include<matrix.h>
#include<iostream>
using namespace std;

class Recursos
{

public:
    Recursos();
    Matrix *getMatrix(string url);
    Matrix *crearEntorno(int n);
    Matrix *crearRecompensas(int n);

};

#endif // RECURSOS_H
