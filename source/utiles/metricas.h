#ifndef METRICAS_H
#define METRICAS_H
#include<QList>
#include<source/utiles/episodio.h>
#include<fstream>
#include<iostream>
using namespace std;
class Metricas
{
private:
    int umbral = -250;
    int acumulador =0; //total derecompensas por episodio.
    int m = 10; // Cantidad de episodios a promediar para medir el humbral -> m ultimos episodios
    QList<Episodio> * historial;




public:
       Metricas();
    void guardarRecompensa(int recompensa);
    bool finalizarEpisodio();
    double getTime();
    void exportarCSV();
    int length();
    int getPromedio();



};

#endif // METRICAS_H
