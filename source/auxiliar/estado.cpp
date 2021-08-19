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

Estado::Estado(int i):index(i)
{
}
