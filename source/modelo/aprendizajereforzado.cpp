#include "aprendizajereforzado.h"
#include<time.h>

AprendizajeReforzado::AprendizajeReforzado(int dimension)
{

    entorno = new Entorno(dimension);
}


void AprendizajeReforzado::initMAAC()
{
    this->qValues = crearQvalues();
}

void AprendizajeReforzado::initMA()
{
    this->agente = new Agente(crearQvalues());
    agente->setExperiencia(new Matrix(1,agente->getQValues()->filas(),agente->getQValues()->columnas()));

}

void AprendizajeReforzado::initSEC()
{
     this->agente = new Agente(crearQvalues());
}

Matrix *AprendizajeReforzado::crearQvalues()
{
    return  new Matrix(entorno->getEntorno()->filas() * entorno->getEntorno()->columnas(),4);
}

void AprendizajeReforzado::entrenarMA(Algoritmo alg,  int it){
#pragma omp declare reduction(mezcla: Agente *: omp_out = omp_out->mezcla(omp_in)) initializer(omp_priv=new Agente(omp_orig))

    initMA();
    int rank;
    int ciclos,i=0 ; //numéro de veces que se van a realizar n cantidad de episodios donde n = frecuencia int size , rank;
    int iteraciones; // número de episodios por ciclo
    bool entrenado = false;
    ciclos = it / frecuencia ;
    iteraciones = frecuencia;

    Agente * agTemp = new Agente(agente);

    while( i<ciclos && !entrenado){
#pragma omp parallel reduction(mezcla:agTemp) private(rank)
        {
            bool temp= false;
            rank = omp_get_thread_num();
            srand(rank + time(NULL));
            temp=  agTemp->entrenarMA(alg,rank,iteraciones,entorno);

            if(rank==0){
                entrenado=temp;
            }
        }


        i++;
    }
    delete agente;
    agente = new Agente(agTemp);
}
/**
 *
 */
void AprendizajeReforzado::entrenarMAAC(Algoritmo alg,  int it){
    initMAAC();
    int  rank=0;
    bool entrenado = false;
#pragma omp parallel private(rank)
    {

        rank = omp_get_thread_num();
        srand(rank + time(NULL));
        Agente * a = new Agente();
        a->entrenarMAAC(alg,rank,it,qValues,entorno,&entrenado);
    }
}
/**
 * Ejecuta los algoritmos de forma secuencial
 */
void AprendizajeReforzado::secuencial(Algoritmo alg, int it)
{


    initSEC();

    srand(time(NULL));

    agente->entrenarSEC(alg,it,entorno);


}




