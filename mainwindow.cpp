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

    remy = new Jugador(100.0f, 600.0f);
    insecto = new Enemigo(400.0f, 550.0f);
    // Remy rectangulo cyan de 40x50 para la prueba
    graficoRemy = escena->addRect(0, 0, 40, 50, QPen(Qt::black), QBrush(Qt::cyan));
    graficoRemy->setPos(remy->obtenerX(), remy->obtenerY());

    // Insecto rectangulo rojo de 60x40
    graficoInsecto = escena->addRect(0, 0, 60, 40, QPen(Qt::black), QBrush(Qt::red));
    graficoInsecto->setPos(insecto->obtenerX(), insecto->obtenerY());
    // Crear el Charco de Lodo
    charcoLodo = new Objeto(600.0f, 580.0f, Objeto::CHARCO, 200.0f, 50.0f);
    graficoCharco = escena->addRect(0, 0, charcoLodo->obtenerAncho(), charcoLodo->obtenerAlto(),  QPen(Qt::NoPen), QBrush(QColor(80, 60, 40, 150)));
    graficoCharco->setPos(charcoLodo->obtenerX(), charcoLodo->obtenerY());

    // Crear la Cadena
    cadena = new Objeto(900.0f, 100.0f, Objeto::CADENA, 10.0f, 300.0f); // 300px de largo
    graficoCadena = escena->addLine(0, 0, 0, cadena->obtenerAlto(), QPen(Qt::gray, 4));
    graficoCadena->setPos(cadena->obtenerX(), cadena->obtenerY());
    // Qt rota desde la esquina superior izquierda, así que el pivote sera el techo

    // Crear la Caja
    caja = new Objeto(300.0f, 560.0f, Objeto::CAJA,60.0f, 40.0f);
    graficoCaja = escena->addRect(0, 0,caja->obtenerAncho(),caja->obtenerAlto(), QPen(Qt::black), QBrush(QColor(139, 69, 19)));
    graficoCaja->setPos(caja->obtenerX(), caja->obtenerY());

    // Crear la piedra visual
    graficoPiedra = escena->addRect(0, 0, 10, 10, QPen(Qt::NoPen), QBrush(Qt::gray));
    graficoPiedra->setVisible(false); //no se muestra hasta que se lance

    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, &MainWindow::actualizarJuego);
    temporizador->start(16); // ~60 FPS
    setFocusPolicy(Qt::StrongFocus);//para que reciba el teclado
    teclaDerechaPresionada = false;//banderas para corregcion del diley
    teclaIzquierdaPresionada = false;
    teclaSaltoPresionada = false;
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
    bool dentroDelCharco = false;//verifica ----remy mide40*50
    if (remy->obtenerX() + 40 > charcoLodo->obtenerX() &&
        remy->obtenerX() < charcoLodo->obtenerX() + charcoLodo->obtenerAncho() &&
        remy->obtenerY() + 50 > charcoLodo->obtenerY()) {
        dentroDelCharco = true;
    }
    remy->establecerEnLodo(dentroDelCharco);
    if (teclaSaltoPresionada && !remy->obtenerColgado()) {
        remy->saltar();
    }
   //cadena
    if (!remy->obtenerEnSuelo() && !remy->obtenerColgado() && remy->obtenerTiempoGracia() <= 0.0f){
        // Calculamos la posicion del extremo de la cadena
        float rad = cadena->obtenerAnguloOscilacion() * M_PI / 180.0f;
        float extremoCadenaX = cadena->obtenerX() + (cadena->obtenerAlto() * std::sin(rad));
        float extremoCadenaY = cadena->obtenerY() + (cadena->obtenerAlto() * std::cos(rad));

        // Si Remy toca el extremo
        if (std::abs(remy->obtenerX() - extremoCadenaX) < 40.0f &&
            std::abs(remy->obtenerY() - extremoCadenaY) < 40.0f) {

            remy->establecerColgado(true);
            cadena->iniciarOscilacion();
            remy->establecerVelocidadX(0);
            remy->establecerVelocidadY(0);
        }
        if (std::abs(remy->obtenerX() - extremoCadenaX) < 40.0f &&
            std::abs(remy->obtenerY() - extremoCadenaY) < 40.0f){
            remy->establecerColgado(true);
            cadena->iniciarOscilacion();
            remy->establecerVelocidadX(0);
            remy->establecerVelocidadY(0);
        }
    }

    if (remy->obtenerColgado()) {
        float rad = cadena->obtenerAnguloOscilacion() * M_PI / 180.0f;

        float extremoCadenaX = cadena->obtenerX() + (cadena->obtenerAlto() * std::sin(rad));
        float extremoCadenaY = cadena->obtenerY() + (cadena->obtenerAlto() * std::cos(rad));

        remy->establecerX(extremoCadenaX - 20.0f);//remy en extremo cadena, -20 porque remy mide 40 ->hitbox
        remy->establecerY(extremoCadenaY);

        if (teclaDerechaPresionada) cadena->darImpulso(1.0f);//impulsos
        if (teclaIzquierdaPresionada) cadena->darImpulso(-1.0f);

        if (teclaSaltoPresionada) {
            remy->establecerColgado(false);
            remy->establecerTiempoGracia(0.5f); // 0.5 de couldown, cambiar si es necesario despues de mas pruebas
            teclaSaltoPresionada = false;
            // impulso de salida
            remy->establecerVelocidadX(cadena->obtenerVelocidadAngular() * 3.0f);
            remy->establecerVelocidadY(-400.0f);
        }//se suelta
    }
    //caja
    //miramos si choca(aabb)
    bool choqueX = (remy->obtenerX()+40 > caja->obtenerX() && remy->obtenerX() < caja->obtenerX() + caja->obtenerAncho());
    bool choqueY = (remy->obtenerY()+50 > caja->obtenerY() && remy->obtenerY() < caja->obtenerY() + caja->obtenerAlto());

    if (choqueX && choqueY && remy->obtenerY()+50 < caja->obtenerY() +5){
        if (remy->obtenerVelocidadX() > 0 && remy->obtenerX() < caja->obtenerX()){//se mueva a la derecha
            caja->establecerX(caja->obtenerX() + remy->obtenerVelocidadX() * dt * 0.5f); //la caja se mueve mas lento por friccion
            remy->establecerX(caja->obtenerX() - 40); // bloquear a remy pa que no traspase
        }
        // lo mismo pero a la izquierda
        else if (remy->obtenerVelocidadX() < 0 && remy->obtenerX() > caja->obtenerX()) {
            caja->establecerX(caja->obtenerX() + remy->obtenerVelocidadX() * dt * 0.5f);
            remy->establecerX(caja->obtenerX() + caja->obtenerAncho());
        }
    }

    if (caja->obtenerVelocidadX() != 0){
    }
    //detectar si esta sobre caja
    bool sobreLaCajaX = (remy->obtenerX() + 40 > caja->obtenerX() && remy->obtenerX() < caja->obtenerX() + caja->obtenerAncho());//cae sobre
    bool sobreLaCajaY = (remy->obtenerY() + 50 >= caja->obtenerY() - 10.0f && remy->obtenerY() + 50 <= caja->obtenerY() + 10.0f);

    if (sobreLaCajaX && sobreLaCajaY && remy->obtenerVelocidadY() >= 0){
        remy->establecerAlturaSuelo(caja->obtenerY() - 50.0f); // 50 es la altura de remy
    } else {
        remy->establecerAlturaSuelo(600.0f);//sino esta sobre, el piso es normal
    }
    // piedra
    Objeto* piedraActual = nullptr;
    for (Objeto* piedra : remy->obtenerPiedrasLanzadas()){
        if (piedra->estaActivo()){
            piedraActual = piedra;
            break;
        }
    }

    if (piedraActual != nullptr) {
        graficoPiedra->setVisible(true);
        graficoPiedra->setPos(piedraActual->obtenerX(), piedraActual->obtenerY());
    } else {
        graficoPiedra->setVisible(false);
    }
    // ruido
    for (Objeto* piedra : remy->obtenerPiedrasLanzadas()) {
        if (!piedra->estaActivo() && piedra->obtenerX() > 0){ //ya choco
            insecto->percibir(remy->obtenerX(), remy->obtenerY(), true, piedra->obtenerX(), piedra->obtenerY());//investiga en esa direc
            piedra->establecerX(-100.0f); //sacamos la piedra pa que no repita la accion
        }
    }
    if (!remy->obtenerColgado()) {
        remy->actualizarFisica(dt);
    }


    // El insecto percibe y actua
    insecto->percibir(remy->obtenerX(), remy->obtenerY(), false, 0, 0);
    insecto->actuar(dt, remy->obtenerX(), remy->obtenerY());

    // Actualizar la parte visual
    graficoRemy->setPos(remy->obtenerX(), remy->obtenerY());
    graficoInsecto->setPos(insecto->obtenerX(), insecto->obtenerY());
    // Actualizar la cadena
    cadena->actualizarFisica(dt);
    // Aplicar la rotación visual
    graficoCadena->setRotation(-cadena->obtenerAnguloOscilacion()); // Agrega el menos
     graficoCaja->setPos(caja->obtenerX(), caja->obtenerY());
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
        teclaSaltoPresionada = true;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        remy->agacharse(true);
        break;
    case Qt::Key_F:
        remy->lanzarPiedra();
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
    case Qt::Key_Space:
    case Qt::Key_Up:
    case Qt::Key_W:
        teclaSaltoPresionada = false;
        break;
    }
}