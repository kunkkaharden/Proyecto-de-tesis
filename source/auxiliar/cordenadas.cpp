#include "cordenadas.h"

int Cordenadas::getF() const
{
    return f;
}

int Cordenadas::getC() const
{
    return c;
}

void Cordenadas::setC(int value)
{
    c = value;
}

void Cordenadas::setF(int value)
{
    f = value;
}

int Cordenadas::getIndex() const
{
    return index;
}

void Cordenadas::setIndex(int value)
{
    index = value;
}

Cordenadas::Cordenadas(int f, int c, int i):f(f), c(c), index(i)
{

}

Cordenadas::Cordenadas(int f, int c):f(f), c(c)
{

}
