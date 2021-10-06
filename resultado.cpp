#include "resultado.h"
#include "ui_resultado.h"

#include "nodo.h"

Resultado::Resultado(QWidget *parent, QList<Nodo *> *caminho, int qtdIteracoes) :
    QDialog(parent),
    ui(new Ui::Resultado) {
    ui->setupUi(this);

    this->caminho = caminho;

    this->timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(updateTimer()));
    timer->start(1000);

    this->ui->labelObjetivo->setVisible(false);

    this->passo = 0;
    this->ui->labelIteracoes->setText(QString::number(qtdIteracoes));
    this->ui->labelQtdPassos->setText(QString::number(this->caminho->size()-1));
    this->ui->labelPasso->setText(QString::number(passo));

    this->inPlay = false;

    connect(ui->playPause,SIGNAL(clicked()),this,SLOT(play()));
    connect(ui->proximoPasso,SIGNAL(clicked()),this,SLOT(next()));
    connect(ui->passoAnterior,SIGNAL(clicked()),this,SLOT(previous()));
    connect(ui->ok,SIGNAL(clicked()),this,SLOT(accept()));
    this->updateMatriz();
}

Resultado::~Resultado()
{
    delete ui;
}

void Resultado::play() {

    if(this->inPlay) {
        this->inPlay = false;
    } else {
        this->inPlay = true;
    }

}

void Resultado::next() {
    if( !(passo >= this->caminho->size()-1)) {
        this->passo++;
    }
    this->updateMatriz();
}

void Resultado::previous() {
    if(!(passo <= 0)) {
        this->passo--;
    }
    this->updateMatriz();
}

void Resultado::updateTimer() {

    if(inPlay) {
        this->next();
    }
}

void Resultado::updateMatriz() {

    QString dado = this->caminho->at(passo)->getDado();

    if(passo == this->caminho->size()-1) {
        ui->labelObjetivo->setVisible(true);
    } else {
        ui->labelObjetivo->setVisible(false);
    }

    for(int i = 0; i < 3; i++) {
        for(int x = 0; x < 3; x++) {
            QTableWidgetItem* item = ui->tablePuzzle->item(i,x);
            int num = dado.at(i*3+x).digitValue();
            if(num == 0) {
                item->setSelected(true);
            } else {
                item->setSelected(false);
            }
            item->setText(dado.at(i*3+x));
        }
    }
    this->ui->labelPasso->setText(QString::number(passo));

}
