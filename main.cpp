#include <QCoreApplication>
#include<omp.h>
#include<iostream>
#include<source/modelo/aprendizajereforzado.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AprendizajeReforzado * ar  = new AprendizajeReforzado(5);
  //  ar->entrenarETComun(SARSA_Learning,10000);
    ar->entrenarETCentral(Q_Learning,200);
    return a.exec();
}
