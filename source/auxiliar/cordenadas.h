#ifndef CORDENADAS_H
#define CORDENADAS_H


class Cordenadas
{
    int f , c , index;
public:
    Cordenadas(int f, int c , int i);
     Cordenadas(int f, int c );
    int getF() const;
    int getC() const;
    void setC(int value);
    void setF(int value);
    int getIndex() const;
    void setIndex(int value);
};

#endif // CORDENADAS_H
