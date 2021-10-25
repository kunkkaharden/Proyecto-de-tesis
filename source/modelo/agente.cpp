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
 * Genera un número aleatorio [0.0, 0.99]
 */
float Agente::floatRandom()
{ 
    float a = 0+ rand() %99;
    return a/100;
}
/**
 * Devuelve una acción aleatoria [0, 3]
 */
int Agente::accionRamdon(Matrix *qValues)
{

    return   0+ rand() % qValues->columnas();
}
/**
 * Devuelve una acción dada la política aprendida [0, 3]
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
 *
 * Busca cual es la acción con mayor valor Q a partir de un estado dado  int [0, 3].
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
/**
 * Disminuye el valor de e
 */
void Agente::disminuirE()
{
    if(e > 0.02){
        e -= 0.01;
    }

}

/**
 *
 * Combina los valores Q de cada a gente a partir de el número de veces que fue actualizado,
 * descartando el valor que menos veces fue actualizado y en caso de empate se hace un promedio entre los 2.
 */
Agente *Agente::mezcla(Agente *a)
{

    float qTemp1, qTemp2;//qvalues temporales
    float eTemp1, eTemp2;//experincias temporales


    int i =0;
    int j =0;

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

        }
    }


    //Se hereda el menor de los 2 valores
    this->getE() < a->getE() ? this->setE(this->getE()) : this->setE(a->getE());
    this->getM()->length() > a->getM()->length() ? this->setM(this->getM()) : this->setM(a->getM());


    delete a;
    return this;
}
/**
 *
 * @return Devuelve el estado inicial de cada episodio.
 */
int Agente::getEstadoInicial(int rank, Matrix * qValues)
{
    int s =0;
    if(rank !=0){
        s = 0  + rand() % qValues->filas();
    }
    return s;

}


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
 * Contructor copia
 */
Agente::Agente(Agente *a)
{
    this->m = a->getM();
    this->qValues = new Matrix(a ->qValues);
    this->experiencia =new Matrix(a ->experiencia);
    this->e = a->e;

}


Agente::Agente(Matrix *q)
{   m = new Metricas();
    this->qValues = q;
    this->experiencia = NULL;
}
/**
 * Q-Learning Secuencial
 */
bool Agente::qLearningSEC( Entorno *entorno)
{
    int pasos =0;
    bool entrenado = false;
    int s =0; // estado actual
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    Estado * est = new Estado(0,0);
    bool bandera = true; //para el fin de episodio
    //**************
    while(bandera){
        pasos++;

        ac = politica(s,qValues);
        delete est;
        est = entorno->accion(ac,s);

        sp = est->getIndex();
        r = est->getRecompensa();
        m->guardarRecompensa(r);
        qValues->num(qValues->num(s,ac) +
                     a *
                     (r + y * qValues->num(sp,mejorAccion(sp,qValues))
                      - qValues->num(s,ac) ),s,ac) ;


        s = sp;

        if(est->isTerminal()  ){
            bandera = false;
            disminuirE();
            entrenado = m->finalizarEpisodio();

        }
        if(pasos > 500000){
            bandera = false;
        }

    }
    return entrenado;
}

/**
 * SARSA-Learning Secuencial
 */
bool Agente::sarsaLearningSEC(Entorno *entorno)
{
    bool entrenado = false;
    int pasos =0;
    int s =0; // estado actual
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    int acp;  // accion siguiente
    Estado * est = new Estado(0,0);
    ac = politica(s,qValues);
    bool bandera = true; //para el fin de episodio
    while(bandera){
        pasos++;

        delete est;
        est = entorno->accion(ac,s); //informacion del estado siguiente

        sp = est->getIndex();
        r = est->getRecompensa();
        if( omp_get_thread_num() == 0){
            m->guardarRecompensa(r);
        }
        acp =  politica(sp,qValues);


        if(!est->isTerminal()){


            qValues->num(qValues->num(s,ac) +
                         a *
                         (r + y * qValues->num(sp,acp)
                          - qValues->num(s,ac) ),s,ac) ;


        }else{

            qValues->num(qValues->num(s,ac) +
                         a *
                         (r  - qValues->num(s,ac) ),s,ac) ;


        }

        s = sp; ac = acp;


        if(est->isTerminal()){
            bandera = false;
            disminuirE();
            entrenado =  m->finalizarEpisodio();
        }
        if(pasos > 500000){
            bandera = false;
        }

    }

    return entrenado;

}
/**
 * Q-Learning para multiagente
 */
bool Agente::qLearningMA(int s,Entorno *entorno)
{
    bool entrenado = false;
    int pasos =0;
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    Estado * est = new Estado(0,0);
    bool bandera = true; //para el fin de episodio
    //**************
    while(bandera){
        pasos++;

        ac = politica(s,qValues);
        delete est;
        est = entorno->accion(ac,s);

        sp = est->getIndex();
        r = est->getRecompensa();
        if( omp_get_thread_num() == 0){
            m->guardarRecompensa(r);
        }


        qValues->num(qValues->num(s,ac) +
                     a *
                     (r + y * qValues->num(sp,mejorAccion(sp,qValues))
                      - qValues->num(s,ac) ),s,ac) ;


        experiencia->num( experiencia->num(s,ac) + 1,s,ac);

        s = sp;

        if(est->isTerminal()  ){
            bandera = false;
            disminuirE();
            if( omp_get_thread_num() == 0){
                entrenado =  m->finalizarEpisodio();
            }

        }
        if(pasos > 500000){
            bandera = false;
        }

    }
    return entrenado ;
}
/**
 * SARSA-Learning Multiagente
 */
bool Agente::sarsaLearningMA(int s,Entorno *entorno)
{

    int  pasos =0;
    bool entrenado = false;
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    int acp;  // accion siguiente
    Estado * est = new Estado(0,0);
    ac = politica(s,qValues);
    bool bandera = true; //para el fin de episodio
    while(bandera){
        pasos++;

        delete est;
        est = entorno->accion(ac,s); //informacion del estado siguiente

        sp = est->getIndex();
        r = est->getRecompensa();
        if( omp_get_thread_num() == 0){
            m->guardarRecompensa(r);
        }
        acp =  politica(sp,qValues);


        if(!est->isTerminal()){


            qValues->num(qValues->num(s,ac) +
                         a *
                         (r + y * qValues->num(sp,acp)
                          - qValues->num(s,ac) ),s,ac) ;


        }else{

            qValues->num(qValues->num(s,ac) +
                         a *
                         (r  - qValues->num(s,ac) ),s,ac) ;


        }

        experiencia->num( experiencia->num(s,ac) + 1,s,ac);

        s = sp; ac = acp;

        if(est->isTerminal()){
            bandera = false;
            disminuirE();
            if( omp_get_thread_num() == 0){
                entrenado =     m->finalizarEpisodio();
            }

        }
        if(pasos > 500000){
            bandera = false;



        }

    }
    return entrenado ;
}

/**
 *Q-Learning Multiagente con actualizacion constante
 */
bool Agente::qLearningMAAC(int s, Matrix *qValues,Entorno *entorno)
{


    bool entrenado= false;
    int pasos= 0;
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    Estado * est = new Estado(0,0);
    bool bandera = true; //para el fin de episodio
    //**************
    while(bandera){
        pasos++;

        ac = politica(s,qValues);
        delete est;
        est = entorno->accion(ac,s);

        sp = est->getIndex();
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

        s = sp;

        if(est->isTerminal()  ){
            bandera = false;
            disminuirE();
            if( omp_get_thread_num() == 0){
              entrenado=  m->finalizarEpisodio();
            }


        }
        if(pasos > 500000){
            bandera = false;



        }

    }
return entrenado;
}


bool Agente::sarsaLearningMAAC(int s, Matrix *qValues,Entorno *entorno)
{

bool entrenado= false;
int pasos= 0;
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    int acp;  // accion siguiente
    Estado * est = new Estado(0,0);
    ac = politica(s,qValues);
    bool bandera = true; //para el fin de episodio
    while(bandera){
        pasos++;

        delete est;
        est = entorno->accion(ac,s); //informacion del estado siguiente

        sp = est->getIndex();
        r = est->getRecompensa();
        if( omp_get_thread_num() == 0){
            m->guardarRecompensa(r);
        }
        acp =  politica(sp,qValues);
        #pragma omp critical
         {

        if(!est->isTerminal()){


            qValues->num(qValues->num(s,ac) +
                         a *
                         (r + y * qValues->num(sp,acp)
                          - qValues->num(s,ac) ),s,ac) ;


        }else{

            qValues->num(qValues->num(s,ac) +
                         a *
                         (r  - qValues->num(s,ac) ),s,ac) ;


        }
        }

        s = sp; ac = acp;


        if(est->isTerminal()){
            bandera = false;
            disminuirE();
            if( omp_get_thread_num() == 0){
               entrenado= m->finalizarEpisodio();
            }
        }
        if(pasos > 500000){
            bandera = false;



        }

    }
  return entrenado;
}


void Agente::entrenarSEC(Algoritmo alg , int it, Entorno *entorno)
{
    int i =0;
    bool entrenado = false;
    while (i < it && !entrenado){

        if(alg == SARSA_Learning){
            entrenado =  sarsaLearningSEC(entorno);
        }else if(alg == Q_Learning){
            entrenado =  qLearningSEC(entorno);
        }
        i++;
    }

}
bool Agente::entrenarMA(Algoritmo alg ,int rank, int it,  Entorno *entorno)
{
    bool entrenado = false;
    int s = 0; // estado inicial
    int i =0;
    while (i < it && !entrenado){

        s = getEstadoInicial(rank,qValues);

        if(alg == SARSA_Learning){
            entrenado =  sarsaLearningMA(s,entorno);
        }else if(alg == Q_Learning){
            entrenado =  qLearningMA(s,entorno);
        }
        i++;
    }
    return entrenado;
}
void Agente::entrenarMAAC(Algoritmo alg ,int rank, int it, Matrix *qValues, Entorno *entorno ,bool *en)
{

    int s = 0; // estado inicial
    bool entrenado = false;
    int i =0;
    while( i < it && !entrenado && !(*en)){

        s = getEstadoInicial(rank,qValues);

        if(alg == SARSA_Learning){
            entrenado =   sarsaLearningMAAC(s,qValues,entorno);
        }else if(alg == Q_Learning){
            entrenado =   qLearningMAAC(s,qValues,entorno);
        }
        if(rank ==0){
            *(en)= entrenado;
        }
        i++;
    }


}

