#ifndef ESTADORECOMPENSA_H
#define ESTADORECOMPENSA_H
#include<source/auxiliar/estado.h>">

class EstadoRecompensa
{
private :
    Estado  * estado;
    float recompensa;
public:
    EstadoRecompensa(Estado * e, float r);
    ~ EstadoRecompensa();

    Estado *getEstado() const;
    void setEstado(Estado *value);
    float getRecompensa() const;
    void setRecompensa(float value);
};

#endif // ESTADORECOMPENSA_H
