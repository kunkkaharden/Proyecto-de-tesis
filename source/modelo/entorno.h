#ifndef ENTORNO_H
#define ENTORNO_H
//#include<matrix.h>
#include<source/utiles/matrix.h>
#include<iostream>
//#include<estado_recompensa.h>
#include<source/auxiliar/estadoRecompensa.h>
//#include <cordenadas.h>
#include<source/auxiliar/cordenadas.h>
#include<source/auxiliar/estado.h>
#include<vector>
#include<QList>


using namespace std;

class Entorno
{
private:
    Matrix * recompensa;
    Matrix * entorno;
    QList<Cordenadas> * mapa;


public:
    Entorno(Matrix * en , Matrix *  re );
    EstadoRecompensa *  accion(int accion, int est);
    void  hacerMapa();
    Cordenadas * toCordenada(int);
    int toInt(Cordenadas * c);
    void mostrar(int accion, Cordenadas *estado);
    bool posible(int s);
    void mostrar(int accion, int estado);
    Matrix *getEntorno() const;
    void setEntorno(Matrix *value);
    Matrix *getRecompensa() const;
    void setRecompensa(Matrix *value);
};

#endif // ENTORNO_H
