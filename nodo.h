#ifndef NODO_H
#define NODO_H

#include <QString>
#include <QList>

class Nodo {
private:

    QString dado;
    QString objetivo;

    int numNodo;
    int g;
    int h;
    int f;

    bool visitado;

    Nodo* pai;

    QList<Nodo *> *possibilidades;

    QString trocaPosicoesDado(int pos1,int pos2);

public:
    static int contadorNodos;
    Nodo(Nodo *pai, QString objetivo, int g);
    ~Nodo();

    static QString matrizParaString(int** matriz);

    bool removerPossibilidade(Nodo* no);

    void setVisitado(bool vis);
    bool isVisitado();

    void setDado(QString dado);
    QString getDado();

    void setG(int g);
    int getG();

    void setPai(Nodo* pai);
    Nodo* getPai();

    int getF();

    void levantarPossibilidadesMovimento();

    int getH();

    int getNumNodo();

    QList<Nodo *> *getPossibilidades();

    QString toString();

    bool equals(Nodo* no);

};

#endif // NODO_H
