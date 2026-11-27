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
    QGraphicsPixmapItem *graficoCaja;
    QGraphicsPixmapItem *graficoPiedra;

    QGraphicsPixmapItem *graficoRemy;
    QGraphicsPixmapItem *graficoInsecto;
    QGraphicsPixmapItem *graficoCharco;
    QGraphicsPixmapItem *graficoCadena;
    QGraphicsPixmapItem *graficoVentana;
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
    QList<QPixmap> framesIdle;
    QList<QPixmap> framesCorrer;
    QList<QPixmap> framesSaltar;
    QList<QPixmap> framesAgachado;
    QList<QPixmap> framesLanzar;
    bool lanzandoPiedra;
    int frameActualRemy;
    QTimer *timerAnimacionRemy;
    QList<QPixmap> framesIdleInsecto;
    QList<QPixmap> framesCaminarInsecto;
    QList<QPixmap> framesCorrerInsecto;
    QList<QPixmap> framesBuscarInsecto;
    QList<QPixmap> framesAtacarInsecto;
    int frameActualInsecto;
    QTimer *timerAnimacionInsecto;

private slots:
    void actualizarJuego();
    void actualizarAnimacionRemy();
    void actualizarAnimacionInsecto();
};

#endif // MAINWINDOW_H