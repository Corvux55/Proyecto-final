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
#include <QGraphicsRectItem>

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
    Objeto *caja;
    QGraphicsRectItem *graficoCaja;
    QGraphicsRectItem *graficoPiedra;

    QGraphicsPixmapItem *graficoRemy;
    QGraphicsPixmapItem *graficoInsecto;
    QGraphicsRectItem *graficoCharco;
    QGraphicsLineItem *graficoCadena;
    QGraphicsRectItem *graficoVentana;
    bool teclaDerechaPresionada;
    bool teclaIzquierdaPresionada;
    bool teclaSaltoPresionada;
    bool teclaJPresionada;
    float ventanaX;
    float ventanaY;
    float ventanaAncho;
    float ventanaAlto;

    bool enNivel2;
    QGraphicsRectItem *zonaAgua;
    QGraphicsRectItem *zonaLodo;
    QGraphicsRectItem *graficoZonaSegura;

    float zonaSeguraX;
    float zonaSeguraY;
    float zonaSeguraAncho;
    float zonaSeguraAlto;
    bool teclaArribaPresionada;
    bool teclaAbajoPresionada;

    bool juegoTerminado;

private slots:
    void actualizarJuego();
};

#endif // MAINWINDOW_H