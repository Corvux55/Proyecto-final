#include "jugador.h"
#include "enemigo.h"
#include <iostream>
#include <vector>

int main() {
    // Instanciamos a Remy y al Insecto en el mapa
    Jugador remy(100.0f, 600.0f);
    Enemigo insecto(400.0f, 600.0f);

    float dt = 0.016f; // Simulando 60 FPS

    std::cout << "=== INICIANDO PRUEBA DE LOGICA ===\n";

    // --- PRUEBA 1: MOVIMIENTO Y DETECCION ---
    std::cout << "\n[PRUEBA 1] Remy corre hacia la derecha y el insecto lo detecta.\n";

    for (int frame = 0; frame < 60; frame++) {
        remy.moverse(1); // Remy se mueve a la derecha
        remy.actualizarFisica(dt);

        // El insecto percibe a Remy (sin ruidos)
        insecto.percibir(remy.obtenerX(), remy.obtenerY(), false, 0, 0);
        insecto.actuar(dt);

        // Imprimimos el estado cada 15 frames
        if (frame % 15 == 0) {
            std::cout << "Frame " << frame
                      << " | Remy X: " << remy.obtenerX()
                      << " | Insecto X: " << insecto.obtenerX()
                      << " | Estado: " << insecto.obtenerEstadoComoTexto() << "\n";
        }
    }

    // --- PRUEBA 2: EL SALTO ---
    std::cout << "\n[PRUEBA 2] Remy salta.\n";
    remy.saltar();
    for (int frame = 0; frame < 40; frame++) {
        remy.actualizarFisica(dt);
        if (frame % 10 == 0) {
            std::cout << "Frame " << frame
                      << " | Remy Y: " << remy.obtenerY() << "\n";
        }
    }

    // --- PRUEBA 3: LA IA APRENDE CON ENGAÑOS ---
    std::cout << "\n[PRUEBA 3] Simulando que Remy engaña al insecto 3 veces.\n";
    // Esto forzara al enemigo a reducir su radio de escucha (aprendizaje)
    insecto.aprender();
    insecto.aprender();
    insecto.aprender();
    std::cout << "El insecto ha aprendido. Ahora es mas desconfiado.\n";

    std::cout << "\n=== FIN DE LA PRUEBA ===\n";
    return 0;
}