#include "estadoRecompensa.h"

Estado * EstadoRecompensa::getEstado() const
{
    return estado;
}

void EstadoRecompensa::setEstado(Estado * value)
{
    estado = value;
}

EstadoRecompensa::EstadoRecompensa(Estado * e, float r):estado(e),recompensa(r)
{

}

EstadoRecompensa::~EstadoRecompensa()
{
    delete estado;
}

float EstadoRecompensa::getRecompensa() const
{
    return recompensa;
}

void EstadoRecompensa::setRecompensa(float value)
{
    recompensa = value;
}



