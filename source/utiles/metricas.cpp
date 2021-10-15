#include "metricas.h"
#include<omp.h>

Metricas::Metricas()
{
    historial = new QList<Episodio>();
    historial->append( Episodio(0,getTime()));
}

void Metricas::guardarRecompensa(int recompensa)
{
    acumulador += recompensa;


}


bool Metricas::finalizarEpisodio()
{
    bool entrenado = false;
    historial->append( Episodio(acumulador,getTime()));
    cout<<'\n'<<acumulador<<" r"<<endl;
    if ( length() > m && getPromedio() > umbral ){
        cout<<"fin"<<endl;
        exportarCSV();
        entrenado = true;
    }


    acumulador =0;
    return entrenado;
}

double Metricas::getTime()
{
    return omp_get_wtime();
}

void Metricas::exportarCSV()
{

    int id = historial->at(0).getTiempo();
    string nombre = "Historial-" + to_string(id)+".csv";
    ofstream f ;
    cout<<nombre<<endl;
    f.open(nombre,ios::out);
    if(f.fail() ){
        cout<<"No se encuentra el archivo"<<endl;
        system("pause");
    }
    string temp = " ,recompensa,tiempo" ;
    f<<temp<<endl;
    for(int i =0; i< historial->length();i++){
        temp = to_string(i)  +","+ to_string(historial->at(i).getRecompensa())+","+ to_string(historial->at(i).getTiempo()) ;

        f<<temp<<endl;

    }
    temp = "tiemPo: ";
    temp += to_string(historial->at(historial->length() -1 ).getTiempo() - historial->at(0).getTiempo());
    f<<temp<<endl;
    f.close();
    cout<<temp<<'\a';


}

int Metricas::length()
{
    return historial->length();
}
/**
 * @brief Metricas::getPromedio
 * @return Promedio del refuerzo de los ultimos 9 episodios
 */
int Metricas::getPromedio()
{
    int refuerzo = acumulador;
    int temp =0;
    if(historial->length()>m){
        int  inicio = historial->length() - m ;
        for (int i = inicio ; i < historial->length(); i ++ ){
            temp += historial->at(i).getRecompensa();
        }
        refuerzo = temp / m;
    }
    return refuerzo;
}
