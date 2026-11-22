#include "mainwindow.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QColor>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent) {
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 1280, 720);
    escena->setBackgroundBrush(QColor(20, 20, 30)); // Fondo oscuro temporal

    vista = new QGraphicsView(escena, this);
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setFixedSize(1280, 720);
    setCentralWidget(vista);

    remy = new Jugador(100.0f, 550.0f);
    insecto = new Enemigo(400.0f, 550.0f);
    // Remy rectangulo cyan de 40x50 para la prueba
    graficoRemy = escena->addRect(0, 0, 40, 50, QPen(Qt::black), QBrush(Qt::cyan));
    graficoRemy->setPos(remy->obtenerX(), remy->obtenerY());

    // Insecto rectangulo rojo de 60x40
    graficoInsecto = escena->addRect(0, 0, 60, 40, QPen(Qt::black), QBrush(Qt::red));
    graficoInsecto->setPos(insecto->obtenerX(), insecto->obtenerY());

    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, &MainWindow::actualizarJuego);
    temporizador->start(16); // ~60 FPS
    setFocusPolicy(Qt::StrongFocus);//para que reciba el teclado
    teclaDerechaPresionada = false;//banderas para corregcion del diley
    teclaIzquierdaPresionada = false;
}

MainWindow::~MainWindow() {
    delete remy;
    delete insecto;
}

void MainWindow::actualizarJuego() {
    float dt = 0.016f;

    // Movimiento continuo basado en banderas->arreglar bug del didely
    if (teclaDerechaPresionada && !teclaIzquierdaPresionada) {
        remy->moverse(1.0f);
    } else if (teclaIzquierdaPresionada && !teclaDerechaPresionada) {
        remy->moverse(-1.0f);
    } else {
        remy->moverse(0.0f);
    }

    remy->actualizarFisica(dt);

    // El insecto percibe y actua
    insecto->percibir(remy->obtenerX(), remy->obtenerY(), false, 0, 0);
    insecto->actuar(dt, remy->obtenerX(), remy->obtenerY());

    // Actualizar la parte visual
    graficoRemy->setPos(remy->obtenerX(), remy->obtenerY());
    graficoInsecto->setPos(insecto->obtenerX(), insecto->obtenerY());
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return; // Ignorar el auto-repeat

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        teclaIzquierdaPresionada = true;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        teclaDerechaPresionada = true;
        break;
    case Qt::Key_Space:
    case Qt::Key_Up:
    case Qt::Key_W:
        remy->saltar();
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        remy->agacharse(true);
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        teclaIzquierdaPresionada = false;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        teclaDerechaPresionada = false;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        remy->agacharse(false);
        break;
    }
}