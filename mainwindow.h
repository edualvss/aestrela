#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QList>

namespace Ui {
class MainWindow;
}

class Nodo;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void executarAlgoritmo(Nodo* inicial, Nodo* final);
    void normalizarTela();
    
public slots:
    void exibirResultado(int status, QList<Nodo*>* caminho,int qtdIteracoes);

private slots:
    void testaEntradas();

private:


//    void verificarDuplicidade(QList<Nodo *> *lista);

//    bool noJaVisitado(Nodo* no,QList<Nodo*> *visitados);
//    Nodo* getMelhorOpcao(QList<Nodo *> *possibilidades);

    QList<Nodo*> * caminho;

    int** matrizObjetivo;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
