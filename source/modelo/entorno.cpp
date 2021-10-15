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

EstadoRecompensa *Entorno::accion(int accion, int est)
{




    Cordenadas * e = toCordenada(est);
    Cordenadas * estado = toCordenada(est);
    switch (accion ) {
    case 0:
        if(e->getF()!=0){
            if(entorno->num(e->getF()-1,e->getC()) != 0){
                delete estado;
                estado = new Cordenadas(e->getF()-1, e->getC());
            }
        }
        break;
    case 1:
        if(e->getC()!= entorno->columnas()-1){
            if(entorno->num(e->getF(),e->getC()+1) != 0){
                delete estado;
                estado = new Cordenadas(e->getF(), e->getC()+1);
            }
        }
        break;
    case 2:
        if(e->getF()!= entorno->filas()-1){
            if(entorno->num(e->getF()+1,e->getC()) != 0){
                delete estado;
                estado = new Cordenadas(e->getF()+1, e->getC());
            }
        }
        break;
    default:// case 4:

        if(e->getC()!= 0){
            if(entorno->num(e->getF(),e->getC()-1) != 0){
                delete estado;
                estado = new Cordenadas(e->getF(), e->getC()-1);
            }
        }
        break;



    }

    // mostrar(accion , estado);

    Estado * retorno = new Estado(toInt(estado));
    if(entorno->num(estado->getF(),estado->getC())== 2){
        retorno->setFin(true);
    }

    EstadoRecompensa * eR = new EstadoRecompensa(retorno , recompensa->num(estado->getF(), estado->getC()));
    delete e;
    delete estado;
    return eR;
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
void Entorno::mostrar(int accion, int estado){
    Cordenadas * e = toCordenada(estado);
    mostrar(accion,e);
    delete e;
}
void Entorno::mostrar(int accion , Cordenadas * estado){
    if(accion == 0){
        cout<<"\n subir: "<<endl;
    }else if (accion == 1){
        cout<<"\n derecha: "<<endl;
    }else if (accion == 2){
        cout<<"\n bajar: "<<endl;
    }else if (accion == 3){
        cout<<"\n izquierda: "<<endl;
    }

    for(int i =0; i < entorno->filas();i++){
        for(int j =0; j < entorno->columnas();j++){
            if(estado->getF() == i && estado->getC() == j ){
                cout<<"@ ";
            }else{

                if(entorno->num(i,j) == 0){
                    cout<<"# ";
                }else if(entorno->num(i,j) == 1){
                    cout<<"_ ";
                }else{
                    cout<<"X ";
                }
                // cout<<entorno->num(i,j)<<" ";
            }

        }
        cout<<endl;
    }
    cout<<"***************"<<endl;
    // system("pause");
}

bool Entorno::posible(int s)
{
    bool p = false;
    Cordenadas * c = toCordenada(s);
    if(entorno->num(c->getF(),c->getC())==1){
        p = true;
    }
    delete c;
    return p ;
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
