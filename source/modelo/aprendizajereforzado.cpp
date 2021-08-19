#include "aprendizajereforzado.h"
#include<source/utiles/recursos.h>
AprendizajeReforzado::AprendizajeReforzado(int dimension)
{

    entorno = new Entorno(Recursos.crearEntorno(dimension),Recursos.crearRecompensas(dimension));
}

void AprendizajeReforzado::initETComun()
{
    this->qValues = crearQvalues();
}

void AprendizajeReforzado::initETCentral()
{
    this->agente = new Agente(crearQvalues());
}

Matrix *AprendizajeReforzado::crearQvalues()
{
    return  new Matrix(entorno->entorno->filas()*entorno->entorno->columnas(),4);
}

