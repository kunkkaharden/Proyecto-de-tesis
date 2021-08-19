#include "arreglofloat.h"
#include<iostream>
#include<omp.h>
using namespace std;
ArregloFloat::ArregloFloat()
{
    arr  = new float[10000001 ];
    fis=10000001;
    log=0;
}
void ArregloFloat:: add(float num){
    arr[log++]= num;
    if(log == fis){
         cout<<"fis "<<log<<endl;
        cout<<"poooooo "<<log<<endl;
        float *temp = new float[fis+1000 ];
        fis += 1000;
        for(int c = 0; c< log;c++){
            temp[c]=arr[c];

        }

        delete[] arr;
        arr = temp;

    }
}

float *ArregloFloat :: getArr(){
    return arr;
}
int ArregloFloat ::getTam(){
    return log;
}
float  ArregloFloat :: removeU(){
    return arr[--log];

}
