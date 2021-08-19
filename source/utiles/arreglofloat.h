#ifndef ARREGLOFLOAT_H
#define ARREGLOFLOAT_H


class ArregloFloat
{
private:
    float *arr;
    int fis =0, log =0;
public:
    ArregloFloat();
   float *getArr();
   void add(float);
   int getTam();
   float removeU();
};

#endif // ARREGLOFLOAT_H
