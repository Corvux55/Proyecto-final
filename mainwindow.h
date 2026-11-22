#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "jugador.h"
#include "enemigo.h"
#include "objeto.h"
#include <QGraphicsLineItem>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *escena;
    QGraphicsView *vista;
    QTimer *temporizador;

    Jugador *remy;
    Enemigo *insecto;
    Objeto *charcoLodo;
    Objeto *cadena;

    QGraphicsRectItem *graficoRemy;
    QGraphicsRectItem *graficoInsecto;
    QGraphicsRectItem *graficoCharco;
    QGraphicsLineItem *graficoCadena;
    bool teclaDerechaPresionada;
    bool teclaIzquierdaPresionada;
    bool teclaSaltoPresionada;

private slots:
    void actualizarJuego();
};

#endif // MAINWINDOW_H