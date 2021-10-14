#include "aprendizajereforzado.h"
#include<time.h>

AprendizajeReforzado::AprendizajeReforzado(int dimension)
{

    entorno = new Entorno(crearEntorno(dimension),crearRecompensas(dimension));
}


void AprendizajeReforzado::initMAAC()
{
    this->qValues = crearQvalues();
}

void AprendizajeReforzado::initMA()
{
    this->agente = new Agente(crearQvalues());
}

Matrix *AprendizajeReforzado::crearQvalues()
{
    return  new Matrix(entorno->getEntorno()->filas() * entorno->getEntorno()->columnas(),4);
}

void AprendizajeReforzado::entrenarMA(Algoritmo alg,  int it){
#pragma omp declare reduction(mezcla: Agente *: omp_out = omp_out->mezcla(omp_in)) initializer(omp_priv=new Agente(omp_orig))

    initETCentral();
    int size , rank;
    int ciclos ; //numéro de veces que se van a realizar n cantidad de episodios donde n = frecuencia int size , rank;
    int iteraciones; // número de episodios por ciclo
    if(it < frecuencia ){
        ciclos = 1;
        iteraciones = it ;
    }
    else{
        ciclos = it / frecuencia ;
        iteraciones = frecuencia;
    }
    Agente * agTemp = new Agente(agente);
    /*    cout<<"Q antes"<<endl;
    agTemp->getQValues()->mostrar();
    cout<<"E antes"<<endl;
    agTemp->getExperiencia()->mostrar();
    system("pause");
    system("cls");*/
    for(int i =0; i<ciclos ; i++){
#pragma omp parallel reduction(mezcla:agTemp) private(rank)
        {

            size = omp_get_num_threads();
            rank = omp_get_thread_num();
            srand(rank + time(NULL));
            agTemp->entrenar(alg,rank,size,iteraciones,agTemp->getQValues(),entorno,true);
        }


        /*     cout<<"Q despues de mezcalr"<<endl;
        agTemp->getQValues()->mostrar();
        cout<<"E despues de mezcalr"<<endl;
        agTemp->getExperiencia()->mostrar();
        system("pause");
        system("cls");
        //agTemp->resetExp();*/

    }
    delete agente;
    agente = new Agente(agTemp);
}
void AprendizajeReforzado::entrenarMAAC(Algoritmo alg,  int it){
    initETComun();
    int size =1, rank=0;

    //#pragma omp parallel private(rank)
    //{
    // size = omp_get_num_threads();
    //  rank = omp_get_thread_num();
    srand(rank + time(NULL));
    Agente * a = new Agente();
    a->entrenar(alg,rank,size,it,qValues,entorno,false);
    // }
}

void AprendizajeReforzado::secuencial(Algoritmo alg, int it)
{
    initETComun();
    int size =1, rank=0;
    srand(time(NULL));
    Agente * a = new Agente();
    a->entrenar(alg,rank,size,it,qValues,entorno,false);

}


/**
 * @brief Recursos::crearEntorno
 * @param n
 * @return Devuelve una matriz que sería la representación del entorno donde actua el agente
 * 1 para todos los posibles estados
 * 2 para la meta
 */
Matrix *AprendizajeReforzado::crearEntorno(int n)
{
    Matrix * r = new Matrix(1,n,n);
    r->num(2,n-1,n-1);
    return r;
}
/**
 * @brief Recursos::crearRecompensas
 * @param n
 * @return Devuelve una matriz con la recompenza obtenida por llegar a cada estado
 * -1 para los estados no terminale
 *  1 para el estado terminal
 */

Matrix *AprendizajeReforzado::crearRecompensas(int n)
{ Matrix * r = new Matrix(-1,n,n);
    r->num(1,n-1,n-1);
    return r;

}

