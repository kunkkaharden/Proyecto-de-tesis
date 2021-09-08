#include "episodio.h"





double Episodio::getTiempo() const
{
    return tiempo;
}



int Episodio::getRecompensa() const
{
    return recompensa;
}

Episodio::Episodio(int recompensa, double tiempo)
{

    this->recompensa = recompensa;
    this->tiempo = tiempo;

}

