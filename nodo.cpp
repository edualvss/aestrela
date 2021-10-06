#include "nodo.h"

#include <iostream>
using namespace std;

int Nodo::contadorNodos=0;

Nodo::Nodo(Nodo* pai,QString objetivo,int g) {

    this->numNodo = Nodo::contadorNodos++;

    this->objetivo = objetivo;


    this->dado = "";
    this->g = g;
    this->h = 0;
    this->f = 0;

    this->visitado = false;

    this->pai = pai;

    this->possibilidades = new QList<Nodo*>();

}

QString Nodo::matrizParaString(int **matriz) {

    QString d = "";
    for(int i = 0; i < 3; i++) {
        for(int x = 0; x < 3; x++) {
            d += QString::number(matriz[i][x]);
        }
    }
    return d;
}

Nodo::~Nodo() {
    this->possibilidades->clear();
    delete this->possibilidades;
}

bool Nodo::removerPossibilidade(Nodo *no) {
    return this->possibilidades->removeOne(no);
}

void Nodo::setVisitado(bool vis) {
    this->visitado = vis;
}

bool Nodo::isVisitado() {
    return this->visitado;
}

void Nodo::setDado(QString dado) {
    this->dado = dado;
}

QString Nodo::getDado() {
    return this->dado;
}

void Nodo::setG(int g) {
    this->g = g;
}

int Nodo::getG() {
    return this->g;
}

void Nodo::setPai(Nodo *pai) {
    this->pai = pai;
}

Nodo* Nodo::getPai() {
    return this->pai;
}

int Nodo::getF() {
    this->f = this->g + this->getH();
    return this->f;
}

int Nodo::getH() {


    int contador = 0;
    for(int i = 0; i < 9; i++) {
        //if(dado.at(i) != '0') {
            if(dado.at(i) == objetivo.at(i)) {
                contador++;
            }
        //}
    }

    return 9 - contador;

}

int Nodo::getNumNodo() {
    return this->numNodo;
}

QList<Nodo *> *Nodo::getPossibilidades() {
    return this->possibilidades;
}

QString Nodo::toString() {


    QString txt = "";
    txt += QString("F= %1, NumNodo: %2, Visitado: %3\n").arg(QString::number(this->getF())).arg(QString::number(this->numNodo)).arg(QString::number(this->visitado));

    for(int i = 0; i < 9; i++) {
        txt += dado.at(i);
        txt += '\t';
        if( i == 2 || i == 5) {
            txt += '\n';
        }
    }
    return txt;
}

bool Nodo::equals(Nodo *no) {

    return (this->dado == no->dado) ? true: false;

}

QString Nodo::trocaPosicoesDado(int pos1, int pos2) {

    if(pos1 == pos2) {
        return dado;
    }

    QChar um = dado.at(pos1);
    QChar dois = dado.at(pos2);

    QString retorno(dado);
    retorno[pos1] = dois;
    retorno[pos2] = um;
    return retorno;

}

void Nodo::levantarPossibilidadesMovimento() {

    int pos0 = -1;
    for(int i = 0; i < 9; i++) {
        if(dado.at(i) == '0') {
            pos0 = i;

            break;
        }
    }

    switch(pos0) {
        case 0:{
            /// 0x0
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(0,1));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(0,3));
            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);
            break;
        }
        case 1:{
            /// 0x1
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(1,0));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(1,2));
            Nodo* n3 = new Nodo(this,this->objetivo,this->g+1);
            n3->setDado(this->trocaPosicoesDado(1,4));

            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);
            this->possibilidades->insert(possibilidades->end(),n3);

            break;
        }
        case 2:{
            /// 0x2
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(2,1));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(2,5));
            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);

            break;
        }
        case 3:{
            /// 1x0
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(3,0));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(3,4));
            Nodo* n3 = new Nodo(this,this->objetivo,this->g+1);
            n3->setDado(this->trocaPosicoesDado(3,6));

            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);
            this->possibilidades->insert(possibilidades->end(),n3);
            break;
        }
        case 4:{
            /// 1x1
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(4,1));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(4,3));
            Nodo* n3 = new Nodo(this,this->objetivo,this->g+1);
            n3->setDado(this->trocaPosicoesDado(4,5));
            Nodo* n4 = new Nodo(this,this->objetivo,this->g+1);
            n4->setDado(this->trocaPosicoesDado(4,7));

            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);
            this->possibilidades->insert(possibilidades->end(),n3);
            this->possibilidades->insert(possibilidades->end(),n4);

            break;
        }
        case 5:{
            /// 1x2
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(5,2));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(5,4));
            Nodo* n3 = new Nodo(this,this->objetivo,this->g+1);
            n3->setDado(this->trocaPosicoesDado(5,8));

            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);
            this->possibilidades->insert(possibilidades->end(),n3);

            break;
        }
        case 6:{
            /// 2x0
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(6,3));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(6,7));

            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);

            break;
        }
        case 7:{
            /// 2x1
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(7,4));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(7,6));
            Nodo* n3 = new Nodo(this,this->objetivo,this->g+1);
            n3->setDado(this->trocaPosicoesDado(7,8));

            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);
            this->possibilidades->insert(possibilidades->end(),n3);

            break;
        }
        case 8:{
            /// 2x2
            Nodo* n1 = new Nodo(this,this->objetivo,this->g+1);
            n1->setDado(this->trocaPosicoesDado(8,5));
            Nodo* n2 = new Nodo(this,this->objetivo,this->g+1);
            n2->setDado(this->trocaPosicoesDado(8,7));

            this->possibilidades->insert(possibilidades->end(),n1);
            this->possibilidades->insert(possibilidades->end(),n2);

            break;
        }

    }

}
