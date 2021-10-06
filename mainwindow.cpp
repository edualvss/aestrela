#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegularExpression>
#include <QMessageBox>

#include "resultado.h"

#include <QDebug>

//#include "nodo.h"
#include "execucao.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->adjustSize();

    this->matrizObjetivo = new int*[3];
    for(int i = 0; i < 3; i++) {
        this->matrizObjetivo[i] = new int[3];
    }

    // Matriz objetivo
    matrizObjetivo[0][0] = 1;     matrizObjetivo[0][1] = 2;     matrizObjetivo[0][2] = 3;
    matrizObjetivo[1][0] = 8;     matrizObjetivo[1][1] = 0;     matrizObjetivo[1][2] = 4;
    matrizObjetivo[2][0] = 7;     matrizObjetivo[2][1] = 6;     matrizObjetivo[2][2] = 5;

    this->ui->progressBar->setVisible(false);
    this->ui->progressBar->setMinimum(0);
    this->ui->progressBar->setMaximum(0);

    for(int i = 0; i < 3; i ++) {
        for(int x = 0; x < 3; x++) {
            this->ui->tableWidget2->item(i,x)->setText(QString::number(matrizObjetivo[i][x]));
        }
    }

    this->ui->tableWidget->resizeColumnsToContents();
    this->ui->tableWidget2->resizeColumnsToContents();

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(testaEntradas()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::testaEntradas() {

    QRegularExpression* expReg = new QRegularExpression("[0-8]");


    int** matriz = new int*[3];
    for(int i = 0; i < 3; i++) {
        matriz[i] = new int[3];
    }
    // Flag que indica a ocorrência de problema nas entradas
    bool flagErr = false;
    // Verifica se possui somente número de 0 a 8
    for(int i = 0; i < 3; i++) {
        for(int x = 0; x < 3; x++) {
            QTableWidgetItem* item = ui->tableWidget->item(i,x);
            if(item != NULL) {
                QString texto = item->text();
                if(expReg->match(texto).hasMatch()){
                    matriz[i][x] = texto.toInt();
                } else {
                    item->setText("Inv.");
                    matriz[i][x] = -1;
                    flagErr = true;
                }

            }
        }
    }

    // Verifica se há repetição de números
    for(int i = 0; i < 3; i++) {
        for(int x = 0; x < 3; x++) {
            if(matriz[i][x] != -1) {
                for(int l = 0; l < 3; l++) {
                    for(int c = 0; c < 3; c++) {
                        if( !(i == l && x == c) ) {
                            if(matriz[i][x] == matriz[l][c]){
                                if(this->ui->tableWidget->item(l,c) != NULL) {
                                    this->ui->tableWidget->item(l,c)->setText("Inv.");
                                    matriz[l][c] = -1;
                                    flagErr = true;
                                }
                            }
                        }
                    }
                }

            }
        }
    }

    QMessageBox msg(this);
    msg.setText(tr("Campo(s) inválido(s).\nPor favor corrija!"));

    if(flagErr) {
        msg.exec();
        for(int i = 0; i < 3; i++) {
            delete matriz[i];
        }
        delete[] matriz;
    } else {
        QString objetivo = Nodo::matrizParaString(this->matrizObjetivo);
        Nodo* final = new Nodo(NULL,objetivo,0);
        final->setDado(objetivo);
        Nodo* inicial = new Nodo(NULL,objetivo,0);
        inicial->setDado(Nodo::matrizParaString(matriz));
        this->executarAlgoritmo(inicial,final);
    }

}

void MainWindow::normalizarTela() {
    this->ui->pushButton->setEnabled(true);
    this->ui->progressBar->setVisible(false);
}

void MainWindow::executarAlgoritmo(Nodo *inicial, Nodo *final) {

    this->ui->progressBar->setVisible(true);
    this->ui->pushButton->setEnabled(false);

    Execucao* simulador = new Execucao(this,inicial,final);
    connect(simulador,SIGNAL(exibirResultado(int,QList<Nodo*>*,int)),this,SLOT(exibirResultado(int,QList<Nodo*>*,int)));

    simulador->start();

}

void MainWindow::exibirResultado(int status, QList<Nodo *> *caminho, int qtdIteracoes) {

    this->normalizarTela();
    if(status == 1) {
        qDebug() << tr("Não encontrado!");
        QMessageBox msg(this);
        msg.setText(tr("Caminho não encontrado"));
        msg.setInformativeText(tr("Quantidade de iterações realizadas: %1").arg(QString::number(qtdIteracoes)));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
   } else {
        qDebug() << "Encontrado!";

        for(int i = 0; i < caminho->size(); i++) {
            qDebug() << caminho->at(i)->toString();
        }
        Resultado* resultado = new Resultado(this,caminho,qtdIteracoes);
        resultado->exec();
        delete resultado;
    }

}
