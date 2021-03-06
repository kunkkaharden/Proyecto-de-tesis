#include "agente.h"
#include<source/auxiliar/ar.h>
#include<source/utiles/metricas.h>
#include<time.h>
Agente ::~Agente(){

    liberarRecursos();


}

void Agente::liberarRecursos()
{
    delete qValues;
    delete experiencia;
}
Matrix *Agente::getQValues() const
{
    return qValues;
}

void Agente::setQValues(Matrix *value)
{
    qValues = value;
}

Matrix *Agente::getExperiencia() const
{
    return experiencia;
}

void Agente::setExperiencia(Matrix *value)
{
    experiencia = value;
}

float Agente::getE() const
{
    return e;
}

void Agente::setE(float value)
{
    e = value;
}

float Agente::getA() const
{
    return a;
}

void Agente::setA(float value)
{
    a = value;
}

float Agente::getY() const
{
    return y;
}

void Agente::setY(float value)
{
    y = value;
}
/**
 * @brief Agente::floatRandom
 * @return float
 * Genera un número aleatorio [0.0, 0.99]
 */
float Agente::floatRandom()
{
    //  srand(time(NULL));
    float a = 0+ rand() %99;
    //  float b = 0 + rand() % 10 ;
    //  float num = 0 +( a/10) + (b / 100) ;
    return a/100;


    /*  float a = 1+ rand() %9;
    float b = 1 + rand() % 9 ;
    float num = 0 +( a/10) + (b / 100) ;
    return num;*/
}
/**
 * @brief Agente::accionRamdon
 * @param qValues
 * @return int [0, 3]
 * Devuelve una acción aleatoria
 */
int Agente::accionRamdon(Matrix *qValues)
{

    return   0+ rand() % qValues->columnas();
}
/**
 * @brief Agente::politica
 * @param estado
 * @param qValues
 * @return int [0, 3]
 * Devuelve una acción dada la política aprendida
 */
int Agente::politica(int estado, Matrix *qValues)
{
    int accion = -1;
    float ramdon = floatRandom();

    if(ramdon < e){
        accion = accionRamdon(qValues);
    }else{
        accion = mejorAccion(estado, qValues);
    }
    return accion;
}
/**
 * @brief Agente::mejorAccion
 * @param estado
 * @param qValues
 * @return int [0, 3]
 * Busca cual es la acción con mayor valor Q a partir de un estado dado.
 *
 */
int Agente::mejorAccion(int estado, Matrix *qValues)
{
    float valor = qValues->num(estado, 0) ;
    float temporal;
    int accion = 0 ;
    int cantI = 1; // cantidad de valores iguales
    for(int i =1; i < qValues->columnas(); i++){
        temporal = qValues->num(estado, i) ;
        if(temporal > valor){
            valor = temporal;
            accion = i;

        }else  if(temporal == valor){
            cantI++;
        }
    }

    if(cantI == qValues->columnas()){
        accion = accionRamdon(qValues);

    }

    return accion  ;
}

void Agente::disminuirE()
{
    if(e > 0.02){
        e -= 0.01;
    }

}
/**
 * @brief Agente::resetExp
 * Vuelve  poner la matrix de experiencias en estado inicial
 */
void Agente::resetExp()
{
    delete this->experiencia;
    this->experiencia = new Matrix(1,this->qValues->filas(),this->qValues->columnas());
}
/**
 * @brief Agente::mezcla
 * @param a
 * @return Agente*
 * Combina los valores Q de cada a gente a partir de el número de veces que fue actualizado,
 * descartando el valor que menos veces fue actualizado y en caso de empate se hace un promedio entre los 2.
 */
Agente *Agente::mezcla(Agente *a)
{
    ;
    float qTemp1, qTemp2;//qvalues temporales
    float eTemp1, eTemp2;//experincias temporales

    /* cout<<"Q mezcla this"<<endl;
  this->getQValues()->mostrar();
  cout<<"E mezcla this"<<endl;
  this->getExperiencia()->mostrar();
  system("pause");
  system("cls");*/

    int i =0;
    int j =0;
#pragma omp parallel for private(j)
    for (i=0; i< a->getQValues()->filas(); i++){
        for (j=0; j< a->getQValues()->columnas(); j++){
            eTemp1 = this->getExperiencia()->num(i,j);
            eTemp2 =  a->getExperiencia()->num(i,j);
            qTemp1 = this->getQValues()->num(i,j);
            qTemp2 = a->getQValues()->num(i,j);

            if ( eTemp1 == eTemp2){
                this->qValues->num((qTemp1+qTemp2)/2,i,j);

            }else if ( eTemp1 < eTemp2){
                this->qValues->num(qTemp2,i,j);
                this->experiencia->num(eTemp2,i,j);
            }
            //  q->num(((qTemp1*eTemp1)+(qTemp2*eTemp2))/(eTemp1 + eTemp2),i,j);
            // eTemp1 > eTemp2 ?  q->num(qTemp1,i,j) : q->num(qTemp2,i,j);
        }
    }


    //Se hereda el menor de los 2 valores
    this->getE() < a->getE() ? this->setE(this->getE()) : this->setE(a->getE());
    this->getM()->length() > a->getM()->length() ? this->setM(this->getM()) : this->setM(a->getM());

    /*
    cout<<"Q mezcla a"<<endl;
    a->getQValues()->mostrar();
    cout<<"E mezcla a"<<endl;
    a->getExperiencia()->mostrar();
    system("pause");
    system("cls");

    cout<<"Q mezcla r"<<endl;
    this->getQValues()->mostrar();
    cout<<"E mezcla r"<<endl;
    this->getExperiencia()->mostrar();
    system("pause");
    system("cls");
    */
    delete a;
    // this->liberarRecursos();
    return this;
}
/**
 * @brief Agente::getEstadoInicial
 * @param rank
 * @param size
 * @param qValues
 * @return Devuelve el estado inicial de cada episodio en dependencia del agen.
 */
int Agente::getEstadoInicial(int rank,int size, Matrix * qValues)
{
    /*int muestra = qValues->filas() / (size-1);
    int inicio = rank * muestra;


    return inicio + rand() % (muestra);*/
    return 0  + rand() % qValues->filas();

}
/**
 * @brief Agente::Agente
 * Constructor en el caso de tabla Q externa
 */
Metricas *Agente::getM() const
{
    return m;
}

void Agente::setM(Metricas *value)
{
    m = value;
}

Agente::Agente()
{   m = new Metricas();
    qValues = NULL;
    experiencia = NULL;

}
/**
 * @brief Agente::Agente
 * @param a
 * Contructor copia
 */
Agente::Agente(Agente *a)
{
    this->m = a->getM();
    this->qValues = new Matrix(a ->qValues);
    this->experiencia =new Matrix(a ->experiencia);
    this->e = a->e;

}
/**
 * @brief Agente::Agente
 * @param q
 * @param e
 * Constructor a partir de la tabla Q y las experienias
 */
Agente::Agente(Matrix *q, Matrix *e)
{   m = new Metricas();
    this->qValues = q;
    this->experiencia =e;

}

Agente::Agente(Matrix *q)
{   m = new Metricas();
    this->qValues = q;
    this->experiencia = new Matrix(1,q->filas(),q->columnas());
}
/**
 * @brief Agente::qLearning
 * @param s
 * @param pasos
 * @param qValues
 * @param entorno
 * @param ec si se está usando el enfoque de tabla central
 */
void Agente::qLearning(int s,int *pasos, Matrix *qValues,Entorno *entorno,bool ec)
{



    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    EstadoRecompensa * est = new EstadoRecompensa(0,0);
    bool bandera = true; //para el fin de episodio
    //**************
    while(bandera){
        (*pasos)++;

        ac = politica(s,qValues);
        delete est;
        est = entorno->accion(ac,s);

        sp = est->getEstado()->getIndex();
        r = est->getRecompensa();
        if( omp_get_thread_num() == 0){
            m->guardarRecompensa(r);
        }

#pragma omp critical
        {
            qValues->num(qValues->num(s,ac) +
                         a *
                         (r + y * qValues->num(sp,mejorAccion(sp,qValues))
                          - qValues->num(s,ac) ),s,ac) ;
        }
        if(ec){
            experiencia->num( experiencia->num(s,ac) + 1,s,ac);
        }
        s = sp;
        /*if(rank == 0){
            entorno->mostrar(ac,s);
            cout<<"rank: "<<rank<<endl;
            system("pause");

        }*/
        if(est->getEstado()->isTerminal()  ){
            bandera = false;
            disminuirE();
            if( omp_get_thread_num() == 0){
                m->finalizarEpisodio();
            }

            //   cout<<"encontro meta"<<endl;
            //  agente->getValues()->mostrar();
            //   system("pause");
        }
        if((*pasos) > 500000){
            bandera = false;


            //   cout<<"Demaciados pasos  >2000"<<endl;
        }

    }

}

void Agente::sarsaLearning(int s,int *pasos, Matrix *qValues,Entorno *entorno, bool ec)
{

    //  if( omp_get_thread_num() == 0){
    //     cout<<e<<" e"<<endl;
    //  }

    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    int acp;  // accion siguiente
    EstadoRecompensa * est = new EstadoRecompensa(0,0);
    ac = politica(s,qValues);
    bool bandera = true; //para el fin de episodio
    while(bandera){
        (*pasos)++;

        delete est;
        est = entorno->accion(ac,s); //informacion del estado siguiente

        sp = est->getEstado()->getIndex();
        r = est->getRecompensa();
        if( omp_get_thread_num() == 0){
            m->guardarRecompensa(r);
        }
          acp =  politica(sp,qValues);
//#pragma omp critical
      // {
             
            if(!est->getEstado()->isTerminal()){


                qValues->num(qValues->num(s,ac) +
                             a *
                             (r + y * qValues->num(sp,acp)
                              - qValues->num(s,ac) ),s,ac) ;


            }else{

                qValues->num(qValues->num(s,ac) +
                             a *
                             (r  - qValues->num(s,ac) ),s,ac) ;


            }
       // }
        if(ec){

            experiencia->num( experiencia->num(s,ac) + 1,s,ac);
        }
        s = sp; ac = acp;
        /*  if(rank == 0){
            entorno->mostrar(ac,s);
            system("pause");

        }*/

        if(est->getEstado()->isTerminal()){
            bandera = false;
            disminuirE();
            if( omp_get_thread_num() == 0){
                m->finalizarEpisodio();
            }
            //   cout<<"encontro meta"<<endl;
            //  agente->getValues()->mostrar();
            //   system("pause");
        }
        if((*pasos) > 500000){
            bandera = false;


            //   cout<<"Demaciados pasos  >2000"<<endl;
        }

    }

}


void Agente::entrenar(Algoritmo alg ,int rank, int size, int it, Matrix *qValues, Entorno *entorno,bool ec)
{

    int s = 0; // estado inicial
    int pasos =0;  // cantidad de pasos
    for(int i =0; i < it ; i++){
        //  cout<<'.';
        pasos =0;
        if (rank !=0){
            s = getEstadoInicial(rank,size,qValues);
        }
        if(alg == SARSA_Learning){
            sarsaLearning(s,&pasos,qValues,entorno,ec);
        }else if(alg == Q_Learning){
            qLearning(s,&pasos,qValues,entorno,ec);
        }

        //  if(rank == 0)
        //    cout<<"pasos: "<<pasos<<" por "<<rank<<endl;

    }

}
int Agente::menor(){
    int rank = omp_get_thread_num();
    int size = omp_get_num_threads();
    int menor ,  mayor , muestra; //rango inferior y superior de los grupos


    if(size == 1){
        menor =0;
        // muestra = mayor = qValues->filas();

    }else if(size > 2){
        muestra = qValues->filas() / (size -1);
        if(rank == 0){
            //  e = 0.30;
            menor =0;
            // mayor = qValues->filas();
        }else if(rank == size - 1){
            menor = (rank -1) * muestra ;
            // mayor = qValues->filas();
        }else{
            menor = (rank -1 )* muestra ;
            //  mayor = (rank ) * muestra ;
        } }
    return menor;
}
int Agente::mayor(){
    int rank = omp_get_thread_num();
    int size = omp_get_num_threads();
    int menor ,  mayor , muestra; //rango inferior y superior de los grupos


    if(size == 1){
        // menor =0;
        mayor = qValues->filas();

    }else if(size > 2){
        muestra = qValues->filas() / (size -1);
        if(rank == 0){
            //  e = 0.30;
            //  menor =0;
            mayor = qValues->filas();
        }else if(rank == size - 1){
            // menor = (rank -1) * muestra ;
            mayor = qValues->filas();
        }else{
            // menor = (rank -1 )* muestra ;
            mayor = (rank ) * muestra ;
        }}
    return mayor;
}
