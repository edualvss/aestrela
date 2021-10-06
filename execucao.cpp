#include "execucao.h"

#include "mainwindow.h"

//#include <QDebug>



Execucao::Execucao(MainWindow *tela, Nodo *inicial, Nodo *final) : QThread(tela){
    this->inicial = inicial;
    this->final = final;
}

void Execucao::run() {

    QList<Nodo *> *fechados = new QList<Nodo *>();

    int contadorIteracoes = 0;
    Nodo::contadorNodos = 1;

    Nodo* atual = inicial;

    while(true) {
        contadorIteracoes++;
        if(atual == NULL) {
            break;
        }
        if(atual->equals(final)) {
            break;
        }
        if(!atual->isVisitado()) {
            atual->levantarPossibilidadesMovimento();
            fechados->insert(fechados->begin(),atual);
            atual->setVisitado(true);
        }


        QList<Nodo *> *possibilidades = atual->getPossibilidades();
        while(true) {
            Nodo* candidatoProximo = this->getMelhorOpcao(possibilidades);
            if(candidatoProximo == NULL) {
                Nodo* pai = atual->getPai();
                atual = pai;
                break;
            } else if(this->noJaVisitado(candidatoProximo,fechados)) {
                atual->removerPossibilidade(candidatoProximo);
            } else {
                atual->removerPossibilidade(candidatoProximo);
                atual = candidatoProximo;
                break;
            }
        }
    }



//    qDebug() << "Quantidade de iteracoes: "+QString::number(contadorIteracoes);
//    this->verificarDuplicidade(fechados);

    if(atual == NULL) {
//        qDebug() << "Nao encontrado!";
        emit this->exibirResultado(1,NULL,contadorIteracoes);
    } else {
//        qDebug() << "Encontrado!";

        QList<Nodo*> *caminho = new QList<Nodo* >();
        for(;atual != NULL;) {
            caminho->insert(caminho->begin(),atual);
            atual = atual->getPai();
        }

//        for(int i = 0; i < caminho->size(); i++) {
//            qDebug() << caminho->at(i)->toString();
//        }
        emit this->exibirResultado(0,caminho,contadorIteracoes);
    }

}

Nodo* Execucao::getMelhorOpcao(QList<Nodo *> *possibilidades) {

    if(possibilidades->size() == 0) {
        return NULL;
    }

    Nodo* melhor = possibilidades->at(0);
    for(int i = 1; i < possibilidades->size(); i++) {
        Nodo* atual = possibilidades->at(i);
        if(atual->getF() < melhor->getF()) {
            melhor = atual;
        }
    }

    return melhor;
}

bool Execucao::noJaVisitado(Nodo *no, QList<Nodo *> *visitados) {

    for(int i = 0; i < visitados->size(); i++) {
        if(visitados->at(i)->equals(no)) {
            return true;
        }
    }
    return false;

}

void Execucao::verificarDuplicidade(QList<Nodo *> *lista) {
//    qDebug() << "Lista size: "+QString::number(lista->size());
    for(int i = 0; i < lista->size()-1; i++) {
        for(int x = i + 1;x < lista->size() ;x++) {
            if(lista->at(i)->equals(lista->at(x))) {
//                qDebug() << "Repetido!";
//                qDebug() << lista->at(i)->toString();
//                qDebug() << "Com";
//                qDebug() << lista->at(x)->toString();
            }
        }
    }
}
