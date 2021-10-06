#ifndef RESULTADO_H
#define RESULTADO_H

#include <QDialog>

#include <QTimer>

#include <QList>

namespace Ui {
class Resultado;
}

class Nodo;

class Resultado : public QDialog {
    Q_OBJECT
    
public:
    explicit Resultado(QWidget *parent,QList<Nodo *>* caminho,int qtdIteracoes);
    ~Resultado();
    
private slots:
    void play();
    void next();
    void previous();

    void updateTimer();

private:

    void updateMatriz();

    QTimer* timer;
    int passo;
    bool inPlay;
    QList<Nodo *> *caminho;
    Ui::Resultado *ui;
};

#endif // RESULTADO_H
