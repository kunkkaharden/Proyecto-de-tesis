#include <QCoreApplication>
#include<omp.h>
#include<iostream>
#include<source/modelo/aprendizajereforzado.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AprendizajeReforzado * ar  = new AprendizajeReforzado(100);
   // ar->secuencial(Q_Learning,10000000);
     //ar->secuencial(SARSA_Learning,10000000);
     
    //ar->entrenarMAAC(Q_Learning,10000000);
    //ar->entrenarMAAC(SARSA_Learning,10000000);
  
   //   ar->entrenarMA(Q_Learning,10000000);
     ar->entrenarMA(SARSA_Learning,10000000);
   return a.exec();
}

