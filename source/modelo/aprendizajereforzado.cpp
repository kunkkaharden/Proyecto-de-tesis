#include "aprendizajereforzado.h"
#include<source/utiles/recursos.h>
#include<time.h>

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
void AprendizajeReforzado::entrenarETComun(Algoritmo alg,  int it){
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
