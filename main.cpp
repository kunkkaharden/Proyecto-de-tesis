#include <QCoreApplication>
#include<omp.h>
#include<iostream>
#include<source/modelo/aprendizajereforzado.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AprendizajeReforzado * ar  = new AprendizajeReforzado(300);
    ar->entrenarETComun(SARSA_Learning,10000000);
  //  ar->entrenarETCentral(SARSA_Learning,10000000);
    return a.exec();
}

