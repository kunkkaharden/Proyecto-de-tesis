#ifndef AGENTE_H
#define AGENTE_H
#include<source/utiles/matrix.h>
#include<source/modelo/entorno.h>
#include<omp.h>
class Agente
{
private:
    Matrix *qValues;
    Matrix *experiencia; //Número de veces que fue cambiado cada valor
    float e = 0.95; //[0-1] para ver la probabilidad de escoger una accion aleatoria
    float a = 0.99;    //[0-1] factor de aprendizaje  0: no se aprende 1: se olvida lo
    //aprendido anteriormente solo se tiene en cuenta la ultima experiencia
    float y = 0.99;    //[0-1] factor de descuento    0: corto plazo  1: largo plazo

public:
    Agente();
     Agente(Agente*);
      Agente(Matrix * q,Matrix * e);
      Agente(Matrix * q);
    Matrix *getQValues() const;
    void setQValues(Matrix *value);
    Matrix *getExperiencia() const;
    void setExperiencia(Matrix *value);
    float getE() const;
    void setE(float value);
    float getA() const;
    void setA(float value);
    float getY() const;
    void setY(float value);
    float floatRandom();
    int accionRamdon(Matrix * qValues);
    int politica(int estado, Matrix * qValues);
    int  mejorAccion(int estado, Matrix * qValues);
    void disminuirE();
    Agente *mezcla(Agente *a);
   int getEstadoInicial(int rank, int size, Matrix *qValues);
    //Declaración para reduccion
#pragma omp declare reduction(mezcla: Agente *: omp_out = omp_out->mezcla(omp_in)) initializer(omp_priv=new Agente(omp_orig))

};

#endif // AGENTE_H
