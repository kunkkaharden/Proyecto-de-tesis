#include "entorno.h"
#include<omp.h>
/**
 * @brief Entorno:: accion
 * @param accion 0: arriba 1: derecha 2: abajo 3: izquierda
 * @return
 *
 */
Matrix *Entorno::getEntorno() const
{
    return entorno;
}

void Entorno::setEntorno(Matrix *value)
{
    entorno = value;
}

Matrix *Entorno::getRecompensa() const
{
    return recompensa;
}

void Entorno::setRecompensa(Matrix *value)
{
    recompensa = value;
}

Entorno::Entorno(int dimension)
{
    entorno= crearEntorno(dimension);
    recompensa= crearRecompensas(dimension);
    hacerMapa();
    
}

Estado *Entorno::accion(int accion, int est)
{

    Cordenadas * estado = toCordenada(est);
    switch (accion ) {
    case 0:
        if(estado->getF()!=0){  
                estado->setF(estado->getF() -1);
        }
        break;
    case 1:
        if(estado->getC()!= entorno->columnas()-1){
                estado->setC(estado->getC()+1);
        }
        break;
    case 2:
        if(estado->getF()!= entorno->filas()-1){
                estado->setF(estado->getF() +1);  
        }
        break;
    default:// case 3:

        if(estado->getC()!= 0){     
               estado->setC(estado->getC()-1);
        }
        break;



    }

    // mostrar(accion , estado);

    Estado * retorno = new Estado(toInt(estado), recompensa->num(estado->getF(), estado->getC()));
    if(entorno->num(estado->getF(),estado->getC())== 2){
        retorno->setFin(true);
    }


    delete estado;
    return retorno;
}

void Entorno::hacerMapa()
{
    int index =0;
    Cordenadas temp = Cordenadas(0,0,0);
    mapa = new QList<Cordenadas>();
    for(int i =0; i < entorno->filas(); i++){
        for(int j =0; j < entorno->columnas(); j++){
            temp.setIndex(index++);
            temp.setF(i);
            temp.setC(j);

            mapa->append(temp);
        }
    }



}

Cordenadas *Entorno::toCordenada(int ind)
{

    return new Cordenadas(mapa->at(ind).getF(),mapa->at(ind).getC(), mapa->at(ind).getIndex());
}
int Entorno::toInt(Cordenadas *c)
{
    return c->getF() * entorno->columnas() + c->getC();
}




/**
 * Devuelve una matriz que sería la representación del entorno donde actua el agente
 * 1 para todos los posibles estados
 * 2 para la meta
 */
Matrix *Entorno::crearEntorno(int n)
{
    Matrix * r = new Matrix(1,n,n);
    r->num(2,n-1,n-1);
    return r;
}
/**
 *  Devuelve una matriz con la recompenza obtenida por llegar a cada estado
 * -1 para los estados no terminale
 *  1 para el estado terminal
 */

Matrix *Entorno::crearRecompensas(int n)
{ Matrix * r = new Matrix(-1,n,n);
    r->num(1,n-1,n-1);
    return r;

}
