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
    const int frecuencia = 7000;
public:
    AprendizajeReforzado(int dimension);
    void initETComun();
    void initETCentral();
    Matrix * crearQvalues();
    void entrenarETComun(Algoritmo alg, int it);
    void entrenarETCentral(Algoritmo alg, int it);

};

#endif // APRENDIZAJEREFORZADO_H
