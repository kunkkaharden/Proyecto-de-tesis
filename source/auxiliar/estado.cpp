#include "estado.h"


bool Estado::isTerminal() const
{
    return fin;
}

void Estado::setFin(bool value)
{
    fin = value;
}

int Estado::getIndex() const
{
    return index;
}

void Estado::setIndex(int value)
{
    index = value;
}

float Estado::getRecompensa() const
{
    return recompensa;
}

void Estado::setRecompensa(float value)
{
    recompensa = value;
}

Estado::Estado(int i, float recompensa):index(i),recompensa(recompensa)
{
}
