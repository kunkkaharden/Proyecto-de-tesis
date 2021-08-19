#include <QCoreApplication>
#include<omp.h>
#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#pragma omp parallel
{
cout<<"hola ";
}
    return a.exec();
}
