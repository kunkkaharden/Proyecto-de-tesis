#include <QCoreApplication>
#include<omp.h>
#include<iostream>
#include<source/modelo/aprendizajereforzado.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AprendizajeReforzado * ar  = new AprendizajeReforzado(100);
    ar->entrenarETComun(SARSA_Learning,10000);
    return a.exec();
}
