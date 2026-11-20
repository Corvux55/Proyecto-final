TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        enemigo.cpp \
        entidad.cpp \
        jugador.cpp \
        main.cpp \
        mainwindow.cpp \
        objeto.cpp

RESOURCES += \
    Recursos.qrc

HEADERS += \
    enemigo.h \
    entidad.h \
    jugador.h \
    mainwindow.h \
    objeto.h

QT += widgets
