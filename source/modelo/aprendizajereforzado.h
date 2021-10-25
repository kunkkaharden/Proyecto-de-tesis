#ifndef APRENDIZAJEREFORZADO_H
#define APRENDIZAJEREFORZADO_H
#include<source/modelo/agente.h>
#include<source/auxiliar/ar.h>

class AprendizajeReforzado
{
private:
    Matrix * qValues;
    Entorno * entorno;
    Agente * agente;
    const int frecuencia = 1000;
public:
    AprendizajeReforzado(int dimension);
    void initMAAC();
    void initMA();
    void initSEC();
    Matrix * crearQvalues();
    void entrenarMAAC(Algoritmo alg, int it);
    void entrenarMA(Algoritmo alg, int it);
    void secuencial(Algoritmo alg, int it);


};

#endif // APRENDIZAJEREFORZADO_H
