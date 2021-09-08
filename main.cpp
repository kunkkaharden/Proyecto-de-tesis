#include <QCoreApplication>
#include<omp.h>
#include<iostream>
#include<source/modelo/aprendizajereforzado.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AprendizajeReforzado * ar  = new AprendizajeReforzado(100);
    ar->entrenarETComun(Q_Learning,100000);
    // ar->entrenarETCentral(Q_Learning,100000);
    return a.exec();
}
