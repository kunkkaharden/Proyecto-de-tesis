#include "recursos.h"
#include<fstream>
//#include<arreglofloat.h>
#include<source/utiles/arreglofloat.h>

Recursos::Recursos()
{

}
/**
 * @brief Recursos::getMatrix
 * @param url
 * @return Devuelve una matriz a partir de un fichero en formato txt o csv
 */
Matrix *Recursos::getMatrix(string url)
{

    ifstream f ;
    cout<<url<<endl;
    f.open(url,ios::in);
    if(f.fail() ){
        cout<<"No se encuentra el archivo"<<endl;
        throw new Matrix(1,1,1);
    }
    ArregloFloat *a = new ArregloFloat();
    string linea;
    char c;
    int filas =0;
    int columnas =0;
    int total =0;
    bool bandera = true;
    bool isnum = false; //para ver si tiene mas de una cifra
    int temp;
    while(!f.eof()){

        c = f.get();
        int f =  atoi(&c);
        if(isdigit(c)){

            if(isnum){
                temp = temp * 10 +  atoi(&c);
            }else{
                temp = atoi(&c);
            }
            isnum = true;
            //  a->add( atoi(&c));
            // total++;

        }else{

            a->add(temp);
           // cout<<temp<<endl;
          //  system("pause");
            total++;
            isnum = false;
            if(bandera){
                columnas++;
                if(c=='\n'){
                    bandera = false;
                }
            }

        }
    }
        filas = total / columnas;
        f.close();
        Matrix *m = new Matrix(filas,columnas,a->getArr());
        //  m->mostrar();
        return m;

}
/**
 * @brief Recursos::crearEntorno
 * @param n
 * @return Devuelve una matriz que sería la representación del entorno donde actua el agente
 * 1 para todos los posibles estados
 * 2 para la meta
 */
 Matrix *Recursos::crearEntorno(int n)
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

Matrix *Recursos::crearRecompensas(int n)
{ Matrix * r = new Matrix(-1,n,n);
    r->num(1,n-1,n-1);
    return r;

}

