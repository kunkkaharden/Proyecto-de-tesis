#include "aprendizajereforzado.h"
#include<source/utiles/recursos.h>
AprendizajeReforzado::AprendizajeReforzado(int dimension)
{
    Recursos * r = new Recursos();
    entorno = new Entorno(r->crearEntorno(dimension),r->crearRecompensas(dimension));
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
    return  new Matrix(entorno->getEntorno()->filas() * entorno->getEntorno()->columnas(),4);
}

void AprendizajeReforzado::entrenarETCentral(Algoritmo alg,  int it){
    initETCentral();
    int ciclos = it / frecuencia; //numéro de veces que se van a realizar n cantidad de episodios donde n = frecuencia int size , rank;
    int size , rank;

    for(int i =0; i<ciclos ; i++){
#pragma omp parallel reduction(mezcla:agente) private(rank)
        agente->entrenarETComun(alg,rank,size,agente->getQValues(),entorno);

    }
}
void AprendizajeReforzado::entrenarETComun(Algoritmo alg,  int it){
    initETComun();
    int size , rank;

#pragma omp parallel private(rank)
    {
        size = omp_get_num_threads();
        rank = omp_get_thread_num();
        Agente * a = new Agente();
        a->entrenarETComun(alg,rank,size,it,qValues,entorno);
    }
}
