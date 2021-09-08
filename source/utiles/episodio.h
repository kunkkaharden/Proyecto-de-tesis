#ifndef EPISODIO_H
#define EPISODIO_H


class Episodio
{

    int recompensa;
    double tiempo;
public:
    Episodio(int recompensa, double);
    double getTiempo() const;
    int getRecompensa() const;
};

#endif // EPISODIO_H
