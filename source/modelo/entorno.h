#ifndef ENTORNO_H
#define ENTORNO_H
#include<source/utiles/matrix.h>
#include<iostream>
#include<source/auxiliar/cordenadas.h>
#include<source/auxiliar/estado.h>
#include<QList>


using namespace std;

class Entorno
{
private:
    Matrix * recompensa;
    Matrix * entorno;
    QList<Cordenadas> * mapa;


public:
    Entorno(int dimension );
    Estado *  accion(int accion, int est);
    void  hacerMapa();
    Cordenadas * toCordenada(int);
    int toInt(Cordenadas * c);
    Matrix *getEntorno() const;
    void setEntorno(Matrix *value);
    Matrix *getRecompensa() const;
    void setRecompensa(Matrix *value);
    Matrix *crearEntorno(int n);
    Matrix *crearRecompensas(int n);
};

#endif // ENTORNO_H
