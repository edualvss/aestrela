#ifndef EXECUCAO_H
#define EXECUCAO_H

#include <QThread>

#include <QList>

#include "nodo.h"

class MainWindow;

class Execucao : public QThread {

    Q_OBJECT

    Nodo* inicial;
    Nodo* final;

public:
    Execucao(MainWindow* tela,Nodo* inicial,Nodo* final);

    void run();

    bool noJaVisitado(Nodo *no, QList<Nodo *> *visitados);
    Nodo* getMelhorOpcao(QList<Nodo *> *possibilidades);
    void verificarDuplicidade(QList<Nodo *> *lista);

signals:
    void exibirResultado(int status,QList<Nodo*>* caminho,int qtdIteracoes);

};

#endif // EXECUCAO_H
