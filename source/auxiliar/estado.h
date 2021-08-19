#ifndef ESTADO_H
#define ESTADO_H


class Estado
{
private:
    int index;
    bool fin = false;
public:
    Estado(int i);

    bool isTerminal() const;
    void setFin(bool value);
    int getIndex() const;
    void setIndex(int value);

};

#endif // ESTADO_H
