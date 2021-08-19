
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

Matrix::Matrix(Matrix * x)
{int i, j;
    cantFilas = x->filas();
    cantColumnas = x->cantColumnas;
    
    matrix = new float[  cantFilas *  cantColumnas];
    //siiiiii
    //#pragma omp parallel for private(j)
    for(  i =0; i < this->filas(); i++)
        for( j =0; j < this->columnas(); j++){
            num(x->num (i,j) ,i,j);
        }
}

Matrix::Matrix( float valor,int x, int y): cantFilas(x), cantColumnas(y)
{
    matrix = new float[x*y];
    
    for(int i = 0; i < filas()*columnas(); i++){
        matrix[i]=valor;
        
    }
    
}
Matrix::Matrix( int x, int y, float a[]): cantFilas(x), cantColumnas(y)
{
    matrix = new float[x*y];

    for(int i = 0; i < filas()*columnas(); i++){
        matrix[i]=a[i];

    }


}



Matrix::Matrix( int x, int y): cantFilas(x), cantColumnas(y)
{
      srand(time(NULL));
    matrix = new float[x*y];
    
    for(int i = 0; i < filas()*columnas(); i++){
        
      //  matrix[i]= 0+ rand() %10;//floatRandom();
         matrix[i]= floatRandom();
        
    }
    
   ///   mostrar();
  //    system("pause");
}
//Matrix :: Matrix ( int x ,int y, float *arr): cantFilas(x), cantColumnas(y) , matrix(arr){}

float Matrix :: num(int x, int y){
    if(x < 0 || x >= filas() || y< 0 ||y >= columnas()){
        cout<<"num get"<<endl;
        cout<<"fuera de rango"<<endl;
        throw new Matrix(1,1);
    }
    return matrix[x*cantColumnas + y];
}

void Matrix :: num(float numero , int x, int y){
    if(x < 0 || x >= filas() || y< 0 ||y >= columnas()){
        throw new Matrix(1,1);
        cout<<"num set"<<endl;
        cout<<"fuera de rango"<<endl;
    }
    matrix[x*cantColumnas + y] = numero;
}



int Matrix :: filas(){
    return cantFilas;
}

int Matrix :: columnas(){
    return cantColumnas;
}
//esta ok
Matrix * Matrix ::productoVectorial(Matrix *mat){
    //  this->mostrar("this");
    //   mat->mostrar("w");
    int i, j,k;
    float a , b;
    float temporal;
    if(columnas() != mat->filas() ){
        cout<<"X vectorial"<<endl;
        cout<<"no coiciden las dimeciones"<<endl;

    }
    Matrix * nMatrix = new Matrix(1,filas(), mat->columnas());
    
#pragma omp parallel for private(j,k,a,b,temporal) 
    for( i =0; i < nMatrix->filas(); i++){
        for( j =0; j < nMatrix->columnas(); j++){
            temporal =0;
            for( k = 0 ;k < columnas(); k++){
                a =  this->num(i,k);
                b =  mat->num(k,j);
                temporal += a * b;
            }
            nMatrix->num(temporal , i, j);
        }
    }
    return nMatrix;
}
//shedule(dynamic,10000) if nMatrix < 15000
//     #pragma omp critical
//   cout<<temporal<<"calculado en: "<<omp_get_thread_num()<<" de: "<<omp_get_num_threads()<<endl;
//esta ok
Matrix *Matrix::operacionEE( char op, Matrix * mat)
{
    if(filas() != mat->filas() || columnas() != mat->columnas()){
        cout<<"oEE"<<endl;
        cout<<"no son del mismo tamaño"<<endl;
        throw new Matrix(1,1);
    }
    int i;
    int j;
    Matrix * nMatrix = new Matrix (0,mat->filas(), mat->columnas());
    //siiiiiiii
    //#pragma omp parallel for private(j)
    for( i =0; i < nMatrix->filas(); i++){
        for( j =0; j < nMatrix->columnas(); j++){
            switch (op) {
            case '+':
                nMatrix->num(num(i,j) + mat->num(i,j),i,j);
                break;
            case '-':
                nMatrix->num(num(i,j) - mat->num(i,j),i,j);
                break;
            case '*':
                nMatrix->num(num(i,j) * mat->num(i,j),i,j);
                break;
            case '/':
                nMatrix->num(num(i,j) / mat->num(i,j),i,j);
                break;
                
            }
            
        }
    }
    return nMatrix;
}/**
 * @brief Matrix::operator -
 * @return se le resta al valor cada elemento de la matriz
 */
Matrix * Matrix :: resta (float num){ //
    
    Matrix * nMatrix = new Matrix(1,filas(), columnas());
    int i;
    int j;
    //  siiiiiiiii
    //#pragma omp parallel for private(j)
    for( i =0; i < filas(); i++){
        for( j =0; j< columnas(); j++){
            nMatrix->num(num - this->num(i,j),i,j);
        }
    }
    return nMatrix;
}
//
Matrix * Matrix::multiplicacionXescalar(float valor){
    Matrix *nMatrix = new Matrix(0,filas(),columnas());
    int i,j;
    //siiiiiiiii
    //#pragma omp parallel for private(j)
    for(i  =0 ; i<filas();i++){
        for(j=0; j<columnas();j++ ){
            nMatrix->num(num(i,j)*valor,i,j);
        }
        
    }
    return nMatrix;
}
Matrix * Matrix :: transpuesta(){
    Matrix * nMatrix = new Matrix(columnas(),filas());
    int i,j;
    //siiiiiiiiii
    //#pragma omp parallel for private(j)
    for( i =0; i < nMatrix->filas(); i++){
        for( j =0; j< nMatrix->columnas(); j++){
            
            nMatrix->num(num(j,i),i,j);
            
            
        }
    }
    return nMatrix;
}/**
 * @brief Matrix::filaVector
 * @param fila
 * @param vector
 * @return multiplica una fila por un vector
 */
float Matrix :: filaVector(int fila, Matrix *vector){
    if(vector->filas() != 1 || vector->columnas() != columnas()){
        cout<<"fila vector"<<endl;
        cout<<"no son del mismo tamaño, o no es un vector"<<endl;
        throw new Matrix(1,1);
    }
    float temp =0;
    int i ;
    
    for( i = 0; i< columnas() ;i++){
        temp += num(fila,i)*vector->num(0,i);
    }
    return temp;
}

float *Matrix::getArreglo()
{
    return matrix;
}
/**
 * @brief Matrix::instMatrix
 * @param ins
 * @param matriz
 * @return multiplica una fila por una matriz
 * ni me acuerdo de esto :(
 */
Matrix * Matrix :: instMatrix(int ins, Matrix * matriz ){
    
    float *arr = new float[columnas()];
    for(int c =0; c< columnas() ; c++){
        arr[c]= num(ins, c);
    }
    Matrix *temp = new Matrix(1,columnas(),arr);
    return matriz->productoVectorial( temp);
    
    
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
/*
Matrix* Matrix ::concatenar(Matrix *nmat, int lugar){
    int x;
    bool select = true; // true primera matriz  false segunada matriz
    Matrix *l; // Izquierda o Arriba
    Matrix *r; // Derecha o abajo
    Matrix *nMatris;
    if(lugar ==1 || lugar ==3){ // Arriba abajo
    
        if(columnas() != nmat->columnas()){
            throw new Matrix(1,1,1);
        }
        
        if(lugar == 1){
            l = nmat;
            r = this;
            
        }else{
            l = this;
            r= nmat;
            
        }
        
        nMatris = new Matrix(2,l->filas() + r->filas() , columnas() );
        x=0;
        
        for(int i =0;i < nMatris->filas();  x++){
            for(int j=0; j < nMatris->columnas() ; j++){
                if(select){
                    nMatris->num(l->num(i,j),i,j);
                    
                }else{
                    nMatris->num(r->num(x,j),i,j);
                }
                //  cout<<i<<"-"<<j<<"-"<<x<<"-"<<nMatris->num(i,j)<<endl;
                
            }
            //     nMatris->mostrar();
            i++;
            if(i == l->filas()){
                select = false;
                x=-1;
            }
            
        }
        
        
    }else{ // Izquierda derecha
        if(filas() != nmat->filas()){
            throw new Matrix(1,1,1);
        }
        if(lugar == 2){
            r = nmat;
            l = this;
            
        }else{
            r = this;
            l= nmat;
            
        }
        
        nMatris= new Matrix(1,filas() , l->columnas()+ r->columnas());
        x=0;
        
        for(int i =0;i < nMatris->columnas();  x++){
            for(int j=0; j < nMatris->filas() ; j++){
                if(select){
                    nMatris->num(l->num(j,i),j,i);
                    
                }else{
                    nMatris->num(r->num(j,x),j,i);
                }
                //  cout<<i<<"-"<<j<<"-"<<x<<"-"<<nMatris->num(j,i)<<endl;
                
            }
            //     nMatris->mostrar();
            i++;
            if(i == l->columnas()){
                select = false;
                x=-1;
            }
            
        }
        
    }
    return nMatris;
}*/
Matrix* Matrix ::concatenar(Matrix *nmat, int lugar){
    int i,j;
    //  bool select = true; // true primera matriz  false segunada matriz
    Matrix *l; // Izquierda o Arriba
    Matrix *r; // Derecha o abajo
    Matrix *nMatris;
    if(lugar ==1 || lugar ==3){ // Arriba abajo
        
        if(columnas() != nmat->columnas()){
            cout<<"concatenar 1.3"<<endl;
            throw new Matrix(1,1,1);
            
        }
        
        if(lugar == 1){
            l = nmat;
            r = this;
            
        }else{
            l = this;
            r= nmat;
            
        }
        
        nMatris = new Matrix(2,l->filas() + r->filas() , columnas() );
        
        
        //#pragma omp parallel for private(j)
        for( i =0;i < l->filas(); i++){
            for( j=0; j < l->columnas() ; j++){
                nMatris->num(l->num(i,j),i,j);
            }
        }
        
        //#pragma omp parallel for private(j)
        for( i =l->filas();i < nMatris->filas();i++  ){
            
            for( j=0; j < nMatris->columnas() ; j++){
                
                
                nMatris->num(  r->num(i - l->filas(),j)     ,i,j);
                
            }
            
        }
        
    }else{ // Izquierda derecha
        if(filas() != nmat->filas()){
            cout<<"concatenar 2.4"<<endl;
            throw new Matrix(1,1,1);
        }
        if(lugar == 2){
            r = nmat;
            l = this;
            
        }else{
            r = this;
            l= nmat;
            
        }
        //r->mostrar("r-concatenar");
        nMatris= new Matrix(1,filas() , l->columnas()+ r->columnas());
        
        //#pragma omp parallel for private (j)
        //  float a;
        for( i =0;i < l->columnas();  i++){
            for( j=0; j < nMatris->filas() ; j++){
                nMatris->num(l->num(j,i),j,i);
            }
        }
        //siiiiiiiii
        //#pragma omp parallel for private(j)
        for( i = l->columnas();i < nMatris->columnas(); i++ ){
            
            for( j=0; j < nMatris->filas() ; j++){
                
                nMatris->num(r->num(j, i - l->columnas()),j,i);
            }
            
        }
    }
    
    //  cout<<"con"<<endl;
    //  nMatris->mostrar();
    return nMatris;
}
float Matrix :: floatRandom(){
    
    float a = 1+ rand() %9;
    // float b = 1 + rand() % 5 ;
    float num = 0 +( a/10) ;//+ (b / 100) ;
    return num;
}
