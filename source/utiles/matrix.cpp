
#include "matrix.h"
#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

using namespace std;
Matrix::~Matrix()
{
    cantColumnas = 0;
    cantFilas =0;
    delete[] matrix;
}

Matrix::Matrix( Matrix *x): cantFilas(x->filas()), cantColumnas( x->columnas())
{
    int size = cantFilas *  cantColumnas;
     matrix = new float[size];
     memcpy(matrix,x->getArreglo(),sizeof(float)*size);
}
Matrix::Matrix( float valor,int x, int y): cantFilas(x), cantColumnas(y)
{
    matrix = new float[x*y];
    
    for(int i = 0; i < filas()*columnas(); i++){
        matrix[i]=valor;
        
    }
    
}


Matrix::Matrix( int x, int y): cantFilas(x), cantColumnas(y)
{
      srand(time(NULL));
    matrix = new float[x*y];
    
    for(int i = 0; i < filas()*columnas(); i++){
        
         matrix[i]= floatRandom();
        
    }
    

}


float Matrix :: num(int x, int y){
    if(x < 0 || x >= filas() || y< 0 ||y >= columnas()){

        throw string("num get: fuera de rango");
    }
    return matrix[x*cantColumnas + y];
}

void Matrix :: num(float numero , int x, int y){
    if(x < 0 || x >= filas() || y< 0 ||y >= columnas()){
        throw string("num set: fuera de rango");

    }
    matrix[x*cantColumnas + y] = numero;
}



int Matrix :: filas(){
    return cantFilas;
}

int Matrix :: columnas(){
    return cantColumnas;
}


float *Matrix::getArreglo()
{
    return matrix;
}

void Matrix:: mostrar(){
    cout<<"the matrix"<<endl;
    int i=0;
    for(int c =0; c < filas() * columnas();c++){
        cout<<matrix[c]<<"   ";
        if(i<columnas()-1){
            i++;
            
        }else{
            i=0;
            cout<<endl;
        }
        
    }
    cout<<"f "<<filas()<<"   c"<<columnas()<<endl;
}

void Matrix::mostrar(string x)
{
    cout<<x<<endl;
    mostrar();
}

float Matrix :: floatRandom(){
    
    float a = 0+ rand() %99;
    return a/100;
}
