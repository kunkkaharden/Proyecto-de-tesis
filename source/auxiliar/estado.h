#ifndef ESTADO_H
#define ESTADO_H


class Estado
{
private:
    int index;
    bool fin = false;
    float recompensa;
public:
    Estado(int i,float recompensa);

    bool isTerminal() const;
    void setFin(bool value);
    int getIndex() const;
    void setIndex(int value);

    float getRecompensa() const;
    void setRecompensa(float value);
};

#endif // ESTADO_H
