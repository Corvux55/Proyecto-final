
#include "mainwindow.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QColor>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent) {
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 1280, 720);
    enNivel2 = false;
    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, &MainWindow::actualizarJuego);
    temporizador->start(16); // ~60 FPS
    setFocusPolicy(Qt::StrongFocus);//para que reciba el teclado
    teclaDerechaPresionada = false;//banderas para corregcion del diley
    teclaIzquierdaPresionada = false;
    teclaSaltoPresionada = false;
    teclaArribaPresionada = false;
    teclaAbajoPresionada= false;
    teclaJPresionada = false;

    if (enNivel2){
        QPixmap fondoNivel2(":/recursos/recursos_juego_transparentes/escenario_nivel2_plaza.png");
        escena->setBackgroundBrush(fondoNivel2.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        QPixmap fondoNivel1(":/recursos/recursos_juego_transparentes/escenario_nivel1_sotano.png");
        escena->setBackgroundBrush(fondoNivel1.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    vista = new QGraphicsView(escena, this);
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setFixedSize(1280, 720);
    setCentralWidget(vista);

    remy = new Jugador(1050.0f, 200.0f);
    insecto = new Enemigo(400.0f, 550.0f);
    framesIdle.append(QPixmap(":/recursos/rat_chef_sprites_transparent/idle/idle1.png"));
    framesIdle.append(QPixmap(":/recursos/rat_chef_sprites_transparent/idle/idle2.png"));
    framesIdle.append(QPixmap(":/recursos/rat_chef_sprites_transparent/idle/idle3.png"));
    framesIdle.append(QPixmap(":/recursos/rat_chef_sprites_transparent/idle/idle4.png"));
    framesIdle.append(QPixmap(":/recursos/rat_chef_sprites_transparent/idle/idle5.png"));

    framesCorrer.append(QPixmap(":/recursos/rat_chef_sprites_transparent/run/run1.png"));
    framesCorrer.append(QPixmap(":/recursos/rat_chef_sprites_transparent/run/run2.png"));
    framesCorrer.append(QPixmap(":/recursos/rat_chef_sprites_transparent/run/run3.png"));
    framesCorrer.append(QPixmap(":/recursos/rat_chef_sprites_transparent/run/run4.png"));
    framesCorrer.append(QPixmap(":/recursos/rat_chef_sprites_transparent/run/run5.png"));

    framesSaltar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/jump/jump1.png"));
    framesSaltar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/jump/jump2.png"));
    framesSaltar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/jump/jump3.png"));
    framesSaltar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/jump/jump4.png"));
    framesSaltar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/jump/jump5.png"));

    framesAgachado.append(QPixmap(":/recursos/rat_chef_sprites_transparent/crouch/crouch1.png"));
    framesAgachado.append(QPixmap(":/recursos/rat_chef_sprites_transparent/crouch/crouch2.png"));
    framesAgachado.append(QPixmap(":/recursos/rat_chef_sprites_transparent/crouch/crouch3.png"));
    framesAgachado.append(QPixmap(":/recursos/rat_chef_sprites_transparent/crouch/crouch4.png"));
    framesAgachado.append(QPixmap(":/recursos/rat_chef_sprites_transparent/crouch/crouch5.png"));

    framesLanzar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/throw/throw1.png"));
    framesLanzar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/throw/throw2.png"));
    framesLanzar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/throw/throw3.png"));
    framesLanzar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/throw/throw4.png"));
    framesLanzar.append(QPixmap(":/recursos/rat_chef_sprites_transparent/throw/throw5.png"));

    lanzandoPiedra = false;

    frameActualRemy = 0;
    graficoRemy = escena->addPixmap(framesIdle[0].scaled(40, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    graficoRemy->setPos(remy->obtenerX(), remy->obtenerY());

    timerAnimacionRemy = new QTimer(this);
    connect(timerAnimacionRemy, &QTimer::timeout, this, &MainWindow::actualizarAnimacionRemy);
    timerAnimacionRemy->start(150);

    framesIdleInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/idle/idle1.png"));
    framesIdleInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/idle/idle2.png"));
    framesIdleInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/idle/idle3.png"));
    framesIdleInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/idle/idle4.png"));
    framesIdleInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/idle/idle5.png"));

    framesCaminarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/walk/walk1.png"));
    framesCaminarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/walk/walk2.png"));
    framesCaminarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/walk/walk3.png"));
    framesCaminarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/walk/walk4.png"));
    framesCaminarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/walk/walk5.png"));

    framesCorrerInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/run/run1.png"));
    framesCorrerInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/run/run2.png"));
    framesCorrerInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/run/run3.png"));
    framesCorrerInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/run/run4.png"));
    framesCorrerInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/run/run5.png"));

    framesBuscarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/search/search1.png"));
    framesBuscarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/search/search2.png"));
    framesBuscarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/search/search3.png"));
    framesBuscarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/search/search4.png"));
    framesBuscarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/search/search5.png"));

    framesAtacarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/attack/attack1.png"));
    framesAtacarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/attack/attack2.png"));
    framesAtacarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/attack/attack3.png"));
    framesAtacarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/attack/attack4.png"));
    framesAtacarInsecto.append(QPixmap(":/recursos/reaper_sprites_transparentes/attack/attack5.png"));

    frameActualInsecto = 0;
    graficoInsecto = escena->addPixmap(framesIdleInsecto[0].scaled(150, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    graficoInsecto->setPos(insecto->obtenerX(), insecto->obtenerY());

    timerAnimacionInsecto = new QTimer(this);
    connect(timerAnimacionInsecto, &QTimer::timeout, this, &MainWindow::actualizarAnimacionInsecto);
    timerAnimacionInsecto->start(150);

    // Crear el Charco de Lodo
    charcoLodo = new Objeto(600.0f, 580.0f, Objeto::CHARCO, 200.0f, 50.0f);
    QPixmap pixmapCharco(":/recursos/recursos_juego_transparentes/charco_lodo.png");
    pixmapCharco = pixmapCharco.scaled(200, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graficoCharco = escena->addPixmap(pixmapCharco);
    graficoCharco->setPos(charcoLodo->obtenerX(), charcoLodo->obtenerY());

    // Crear la Cadena
    cadena = new Objeto(900.0f, 100.0f, Objeto::CADENA, 10.0f, 300.0f); // 300px de largo
    QPixmap pixmapCadena(":/recursos/recursos_juego_transparentes/cadena.png");
    pixmapCadena = pixmapCadena.scaled(40, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    graficoCadena = escena->addPixmap(pixmapCadena);
    graficoCadena->setPos(cadena->obtenerX(), cadena->obtenerY());
    // Qt rota desde la esquina superior izquierda, así que el pivote sera el techo

    // Crear la Caja
    caja = new Objeto(100.0f, 600.0f, Objeto::CAJA,120.0f, 80.0f);
    QPixmap pixmapCaja(":/recursos/recursos_juego_transparentes/caja.png");
    pixmapCaja = pixmapCaja.scaled(120, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graficoCaja = escena->addPixmap(pixmapCaja);
    graficoCaja->setPos(caja->obtenerX(), caja->obtenerY());

    // Crear la piedra visual
    QPixmap pixmapPiedra(":/recursos/recursos_juego_transparentes/piedra_arrojadiza_redonda.png"); // Ajusta la ruta
    pixmapPiedra = pixmapPiedra.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    graficoPiedra = escena->addPixmap(pixmapPiedra);
    graficoPiedra->setVisible(false);//no se muestra hasta que se lance

    juegoTerminado = false;
    ventanaX = 1100.0f;
    ventanaY = 200.0f;
    ventanaAncho = 100.0f;
    ventanaAlto = 150.0f;

    // Zona de Agua
    zonaAgua = escena->addRect(300, 300, 200, 150, QPen(Qt::blue), QBrush(QColor(0, 0, 255, 80)));
    zonaAgua->setVisible(false);

    // Zona de Lodo
    zonaLodo = escena->addRect(700, 400, 250, 200, QPen(Qt::darkYellow), QBrush(QColor(80, 60, 40, 120)));
    zonaLodo->setVisible(false);

    // Zona Segura (meta del Nivel 2)
    zonaSeguraX = 500.0f;
    zonaSeguraY = 50.0f;
    zonaSeguraAncho = 300.0f;
    zonaSeguraAlto = 100.0f;
    graficoZonaSegura = escena->addRect(zonaSeguraX, zonaSeguraY, zonaSeguraAncho, zonaSeguraAlto,QPen(Qt::green, 3), QBrush(QColor(0, 255, 0, 50)));
    graficoZonaSegura->setVisible(false);

    // dibujar la ventana
    QPixmap pixmapVentana(":/recursos/recursos_juego_transparentes/ventana_salida.png"); // Ajusta la ruta
    pixmapVentana = pixmapVentana.scaled(ventanaAncho, ventanaAlto, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    graficoVentana = escena->addPixmap(pixmapVentana);
    graficoVentana->setPos(ventanaX, ventanaY);
    graficoVentana->setVisible(true);

    // nivel2 objetos
    //agua
    QGraphicsRectItem *zonaAgua = escena->addRect(300, 300, 200, 150, QPen(Qt::blue), QBrush(QColor(0, 0, 255, 80)));
    zonaAgua->setVisible(false); //no se muestra en n1

    //lodo
    QGraphicsRectItem *zonaLodo = escena->addRect(700, 400, 250, 200, QPen(Qt::darkYellow), QBrush(QColor(80, 60, 40, 120)));
    zonaLodo->setVisible(false);

}

MainWindow::~MainWindow() {
    delete remy;
    delete insecto;
}

void MainWindow::actualizarJuego() {
    float dt = 0.016f;
    if (!enNivel2){
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
                insecto->percibir(remy->obtenerX(), remy->obtenerY(), true, piedra->obtenerX(), piedra->obtenerY(),false);//investiga en esa direc
                piedra->establecerX(-100.0f); //sacamos la piedra pa que no repita la accion
            }
        }
        if (!remy->obtenerColgado()) {
            remy->actualizarFisica(dt);
        }

        // colision enemigo con caja
        bool choqueInsectoX = (insecto->obtenerX() + 60 > caja->obtenerX() && insecto->obtenerX() < caja->obtenerX() + caja->obtenerAncho());
        bool choqueInsectoY = (insecto->obtenerY() + 40 > caja->obtenerY() && insecto->obtenerY() < caja->obtenerY() + caja->obtenerAlto());

        if (choqueInsectoX && choqueInsectoY){
            float penIzq = (insecto->obtenerX() + 60) - caja->obtenerX();
            float penDer = (caja->obtenerX() + caja->obtenerAncho()) - insecto->obtenerX();
            float penArr = (insecto->obtenerY() + 40) - caja->obtenerY();
            float penAba = (caja->obtenerY() + caja->obtenerAlto()) - insecto->obtenerY();

            float minPen = std::min({penIzq, penDer, penArr, penAba});

            if (minPen == penIzq) {
                insecto->establecerX(insecto->obtenerX() - penIzq);
                insecto->establecerVelocidadX(0.0f);
            } else if (minPen == penDer) {
                insecto->establecerX(insecto->obtenerX() + penDer);
                insecto->establecerVelocidadX(0.0f);
            } else if (minPen == penArr) {
                insecto->establecerY(insecto->obtenerY() - penArr);
                insecto->establecerVelocidadY(0.0f);
            } else {
                insecto->establecerY(insecto->obtenerY() + penAba);
                insecto->establecerVelocidadY(0.0f);
            }
        }

        // El insecto percibe y actua
        insecto->percibir(remy->obtenerX(), remy->obtenerY(), false, 0, 0,false);
        insecto->actuar(dt, remy->obtenerX(), remy->obtenerY());

        // Actualizar la parte visual
        graficoRemy->setPos(remy->obtenerX(), remy->obtenerY());
        graficoInsecto->setPos(insecto->obtenerX(), insecto->obtenerY());
        // Actualizar la cadena
        cadena->actualizarFisica(dt);
        // Aplicar la rotacion visual
        graficoCadena->setRotation(-cadena->obtenerAnguloOscilacion()); // Agrega el menos
        graficoCaja->setPos(caja->obtenerX(), caja->obtenerY());
        //fin del juego
        if (!juegoTerminado){
            //gameover
            float distX = std::abs(remy->obtenerX() - insecto->obtenerX());
            float distY = std::abs(remy->obtenerY() - insecto->obtenerY());
            if (distX < 50.0f && distY < 20.0f) {
                qDebug() << "¡GAME OVER! El insecto atrapó a Remy.";
                juegoTerminado = true;
                temporizador->stop();
            }

            //completo nivel
            if (remy->obtenerX() > ventanaX && remy->obtenerX() < ventanaX + ventanaAncho &&
                remy->obtenerY() > ventanaY && remy->obtenerY() < ventanaY + ventanaAlto) {

                qDebug() << "¡NIVEL 1 COMPLETADO! Pasando al Nivel 2...";

                enNivel2 = true;
                QPixmap fondoNivel2(":/recursos/recursos_juego_transparentes/escenario_nivel2_plaza.png");
                escena->setBackgroundBrush(fondoNivel2.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
                //visibes zonas n2
                graficoZonaSegura->setVisible(true);
                zonaAgua->setVisible(true);
                zonaLodo->setVisible(true);

                //reposiona abajo pa que cruce la plza
                remy->establecerX(640.0f);
                remy->establecerY(650.0f);

                //oculta graficos nivel1
                graficoCharco->setVisible(false);
                graficoCadena->setVisible(false);
                graficoVentana->setVisible(false);
                // caja
                caja->establecerX(600.0f);
                caja->establecerY(300.0f);
                graficoCaja->setPos(caja->obtenerX(), caja->obtenerY());
                graficoCaja->setVisible(true);

                insecto->establecerX(640.0f);
                insecto->establecerY(200.0f);
            }
        }
    }
    else{//logica nivel2
        if (teclaDerechaPresionada && !teclaIzquierdaPresionada) remy->moverse(1.0f);
        else if (teclaIzquierdaPresionada && !teclaDerechaPresionada) remy->moverse(-1.0f);
        else remy->moverse(0.0f);

        if (teclaArribaPresionada && !teclaAbajoPresionada) remy->moverseVertical(-1.0f);
        else if (teclaAbajoPresionada && !teclaArribaPresionada) remy->moverseVertical(1.0f);
        else remy->moverseVertical(0.0f);

        remy->actualizarFisicaTopDown(dt);
        //piedra
        Objeto* piedraActual = nullptr;
        for (Objeto* piedra : remy->obtenerPiedrasLanzadas()){
            if (piedra->estaActivo()) {
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
        //ruido piedra
        for (Objeto* piedra : remy->obtenerPiedrasLanzadas()){
            if (!piedra->estaActivo() && piedra->obtenerX() > 0){
                insecto->percibir(remy->obtenerX(), remy->obtenerY(), true, piedra->obtenerX(), piedra->obtenerY(), false);
                piedra->establecerX(-100.0f);
            }
        }

        //colision caja
        bool choqueX = (remy->obtenerX() + 40 > caja->obtenerX() && remy->obtenerX() < caja->obtenerX() + caja->obtenerAncho());
        bool choqueY = (remy->obtenerY() + 50 > caja->obtenerY() && remy->obtenerY() < caja->obtenerY() + caja->obtenerAlto());

        if (choqueX && choqueY) {

            float penetracionIzquierda = (remy->obtenerX() + 40) - caja->obtenerX();
            float penetracionDerecha = (caja->obtenerX() + caja->obtenerAncho()) - remy->obtenerX();
            float penetracionArriba = (remy->obtenerY() + 50) - caja->obtenerY();
            float penetracionAbajo = (caja->obtenerY() + caja->obtenerAlto()) - remy->obtenerY();


            float minPenetracion = std::min({penetracionIzquierda, penetracionDerecha, penetracionArriba, penetracionAbajo});
            if (minPenetracion == penetracionIzquierda) {
                remy->establecerX(remy->obtenerX() - penetracionIzquierda);
                remy->establecerVelocidadX(0.0f);
            } else if (minPenetracion == penetracionDerecha) {
                remy->establecerX(remy->obtenerX() + penetracionDerecha);
                remy->establecerVelocidadX(0.0f);
            } else if (minPenetracion == penetracionArriba) {
                remy->establecerY(remy->obtenerY() - penetracionArriba);
                remy->establecerVelocidadY(0.0f);
            } else {
                remy->establecerY(remy->obtenerY() + penetracionAbajo);
                remy->establecerVelocidadY(0.0f);
            }
        }

        if (remy->obtenerX() < 0) remy->establecerX(0);
        if (remy->obtenerX() > 1240) remy->establecerX(1240);
        if (remy->obtenerY() < 0) remy->establecerY(0);
        if (remy->obtenerY() > 670) remy->establecerY(670);

        graficoRemy->setPos(remy->obtenerX(), remy->obtenerY());

        // remy agua
        bool enAgua = (remy->obtenerX() > 300 && remy->obtenerX() < 500 && remy->obtenerY() > 300 && remy->obtenerY() < 450);
        // remy lodo
        if (remy->obtenerX() > 700 && remy->obtenerX() < 950 &&
            remy->obtenerY() > 400 && remy->obtenerY() < 600) {
            remy->establecerEnLodo(true);
        } else {
            remy->establecerEnLodo(false);
        }

        bool escondido = false;
        if (remy->obtenerAgachado()) {
            bool choqueX = (remy->obtenerX() + 40 > caja->obtenerX() && remy->obtenerX() < caja->obtenerX() + caja->obtenerAncho());
            bool choqueY = (remy->obtenerY() + 50 > caja->obtenerY() && remy->obtenerY() < caja->obtenerY() + caja->obtenerAlto());

            if (choqueX && choqueY) {
                escondido = true;
                qDebug() << "Remy escondido detrás de la caja en Nivel 2.";
            }
        }
        // ya el radio de vision es un circulo
        //si hay ruido pasa coor de remy
        insecto->percibir(remy->obtenerX(), remy->obtenerY(), enAgua, remy->obtenerX(), remy->obtenerY(),escondido);
        insecto->actuar(dt, remy->obtenerX(), remy->obtenerY());//actuar

        // colision enemigi caja
        bool choqueInsectoX = (insecto->obtenerX() + 60 > caja->obtenerX() && insecto->obtenerX() < caja->obtenerX() + caja->obtenerAncho());
        bool choqueInsectoY = (insecto->obtenerY() + 40 > caja->obtenerY() && insecto->obtenerY() < caja->obtenerY() + caja->obtenerAlto());

        if (choqueInsectoX && choqueInsectoY) {

            float penIzq = (insecto->obtenerX() + 60) - caja->obtenerX();
            float penDer = (caja->obtenerX() + caja->obtenerAncho()) - insecto->obtenerX();
            float penArr = (insecto->obtenerY() + 40) - caja->obtenerY();
            float penAba = (caja->obtenerY() + caja->obtenerAlto()) - insecto->obtenerY();


            float minPen = std::min({penIzq, penDer, penArr, penAba});

            if (minPen == penIzq) {
                insecto->establecerX(insecto->obtenerX() - penIzq);
                insecto->establecerVelocidadX(0.0f);
            } else if (minPen == penDer) {
                insecto->establecerX(insecto->obtenerX() + penDer);
                insecto->establecerVelocidadX(0.0f);
            } else if (minPen == penArr) {
                insecto->establecerY(insecto->obtenerY() - penArr);
                insecto->establecerVelocidadY(0.0f);
            } else {
                insecto->establecerY(insecto->obtenerY() + penAba);
                insecto->establecerVelocidadY(0.0f);
            }
        }

        graficoInsecto->setPos(insecto->obtenerX(), insecto->obtenerY());

        //gameover
        float distX = std::abs(remy->obtenerX() - insecto->obtenerX());
        float distY = std::abs(remy->obtenerY() - insecto->obtenerY());

        if (distX < 50.0f && distY < 20.0f){
            juegoTerminado = true;
            temporizador->stop();
        }
        // final nivel
        if (remy->obtenerX() > zonaSeguraX && remy->obtenerX() < zonaSeguraX + zonaSeguraAncho &&
            remy->obtenerY() > zonaSeguraY && remy->obtenerY() < zonaSeguraY + zonaSeguraAlto){
            juegoTerminado = true;
            temporizador->stop();
        }
    }
}

void MainWindow::actualizarAnimacionRemy() {
    QList<QPixmap> *animacionActual = &framesIdle;
    int velocidadDeseada = 150;

    if (lanzandoPiedra) {
        animacionActual = &framesLanzar;
        velocidadDeseada = 60;
        if (frameActualRemy >= framesLanzar.size() - 1){
            lanzandoPiedra = false;
            frameActualRemy = 0;
        }
    } else if (!remy->obtenerEnSuelo()){
        animacionActual = &framesSaltar;
        velocidadDeseada = 100;
    } else if (remy->obtenerAgachado()){
        animacionActual = &framesAgachado;
        velocidadDeseada = 250;
    } else if (teclaDerechaPresionada || teclaIzquierdaPresionada){
        animacionActual = &framesCorrer;
        velocidadDeseada = 100;
    } else {
        animacionActual = &framesIdle;
        velocidadDeseada = 300;
    }

    // ajusta el temporizador si cambio
    if (timerAnimacionRemy->interval() != velocidadDeseada){
        timerAnimacionRemy->setInterval(velocidadDeseada);
    }

    if (animacionActual->isEmpty()) return;

    frameActualRemy = (frameActualRemy + 1) % animacionActual->size();
    graficoRemy->setPixmap((*animacionActual)[frameActualRemy].scaled(40, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::actualizarAnimacionInsecto(){
    QList<QPixmap> *animacionActual = &framesIdleInsecto;
    int velocidadDeseada = 200;

    Enemigo::Estado estado = insecto->obtenerEstado();

    if (estado == Enemigo::PERSIGUIENDO){
        animacionActual = &framesCorrerInsecto;
        velocidadDeseada = 80;
    } else if (estado == Enemigo::INVESTIGANDO){
        animacionActual = &framesBuscarInsecto;
        velocidadDeseada = 120;
    } else{
        if (insecto->obtenerVelocidadX() != 0 || insecto->obtenerVelocidadY() != 0) {
            animacionActual = &framesCaminarInsecto;
            velocidadDeseada = 150;
        } else {
            animacionActual = &framesIdleInsecto;
            velocidadDeseada = 250;
        }
    }

    if (timerAnimacionInsecto->interval() != velocidadDeseada){
        timerAnimacionInsecto->setInterval(velocidadDeseada);
    }

    if (animacionActual->isEmpty()) return;

    frameActualInsecto = (frameActualInsecto + 1) % animacionActual->size();
    graficoInsecto->setPixmap((*animacionActual)[frameActualInsecto].scaled(150,70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
        teclaArribaPresionada =true;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        teclaAbajoPresionada = true;
        if (!enNivel2) {
            remy->agacharse(true);
        }
        break;
    case Qt::Key_F:
        if (enNivel2) {
            float dirX = 0, dirY = 0;
            if (teclaDerechaPresionada) dirX = 1;
            if (teclaIzquierdaPresionada) dirX = -1;
            if (teclaArribaPresionada) dirY = -1;
            if (teclaAbajoPresionada) dirY = 1;
            if (dirX == 0 && dirY == 0) dirX = 1;
            remy->lanzarPiedraRecta(dirX, dirY);
        } else {
            remy->lanzarPiedra();
        }
        lanzandoPiedra = true;
        frameActualRemy =0;
        break;
    case Qt::Key_J:
        teclaJPresionada = true;
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
        teclaAbajoPresionada = false;
        if (!enNivel2) {
            remy->agacharse(false);
        }
        break;
    case Qt::Key_Space:
    case Qt::Key_Up:
    case Qt::Key_W:
        teclaSaltoPresionada = false;
        teclaArribaPresionada = false;
        break;
    case Qt::Key_J:
        teclaJPresionada = false;
        remy->agacharse(false);
        break;
    }
}