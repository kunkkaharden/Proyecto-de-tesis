#ifndef APRENDIZAJEREFORZADO_H
#define APRENDIZAJEREFORZADO_H
#include<source/modelo/agente.h>

class AprendizajeReforzado
{
private:
    Matrix * qValues;
    Entorno * entorno;
    Agente * agente;
public:
    AprendizajeReforzado(int dimension);
    void initETComun();
    void initETCentral();
    Matrix * crearQvalues();
};

#endif // APRENDIZAJEREFORZADO_H
