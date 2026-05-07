#include "Reproductor.h"

#include "input/Keyboard.h"
#include "utils/Console.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

namespace Reproductor {

    void iniciar(
        Cola<Multimedia*>& listaReproduccion
    ) {

        if (listaReproduccion.estaVacia()) {

            cout
                << "Tu lista de reproduccion esta vacia.\n";

            return;
        }

        //
        // Historial de reproduccion
        //
        Pila<Multimedia*> historial;

        //
        // Mostrar contenido actual de la cola
        //
        cout << "Contenido en cola:\n";

        listaReproduccion.procesar(
            [](Multimedia*& m) {

                cout
                    << " - "
                    << m->getTitle()
                    << " ("
                    << m->getYear()
                    << ")\n";
            }
        );

        //
        // Lambda para imprimir tiempo HH:MM:SS
        //
        auto imprimirTiempo =
            [](int totalSegundos) {

                int h =
                    totalSegundos / 3600;

                int m =
                    (totalSegundos % 3600) / 60;

                int s =
                    totalSegundos % 60;

                cout
                    << setfill('0')
                    << setw(2)
                    << h
                    << ":"

                    << setw(2)
                    << m
                    << ":"

                    << setw(2)
                    << s;
            };

        //
        // Reproduccion FIFO
        //
        while (!listaReproduccion.estaVacia()) {

            Multimedia* actual =
                listaReproduccion.obtenerFrente();

            if (actual) {

                //
                // Guardar en historial
                //
                historial.apilar(actual);

                Console::clear();

                cout
                    << "\n=======================================\n";

                cout
                    << "Reproduciendo: "
                    << actual->getTitle()
                    << "\n";

                cout
                    << "Controles:\n";

                cout
                    << "[P] Pausa/Reanudar\n";

                cout
                    << "[S] Saltar\n";

                cout
                    << "[Q] Salir\n";

                cout
                    << "=======================================\n";

                //
                // Convertimos minutos a segundos
                //
                int duracionSeg =
                    actual->getDuration() * 60;

                int tiempoActual = 0;

                bool pausado = false;
                bool saltar = false;
                bool salir = false;

                //
                // Simulacion de reproduccion
                //
                while (
                    tiempoActual <= duracionSeg &&
                    !saltar &&
                    !salir
                ) {

                    //
                    // Input sin bloquear
                    //
                    if (Keyboard::kbhit()) {

                        char tecla =
                            Keyboard::getch();

                        if (
                            tecla == 'P' ||
                            tecla == 'p'
                        ) {

                            pausado = !pausado;
                        }

                        if (
                            tecla == 'S' ||
                            tecla == 's'
                        ) {

                            saltar = true;
                        }

                        if (
                            tecla == 'Q' ||
                            tecla == 'q'
                        ) {

                            salir = true;
                        }
                    }

                    //
                    // Barra de tiempo
                    //
                    cout << "\r[";

                    imprimirTiempo(tiempoActual);

                    cout << "/";

                    imprimirTiempo(duracionSeg);

                    cout << "] ";

                    if (pausado) {

                        cout
                            << "[PAUSADO]     ";
                    }
                    else {

                        cout
                            << "               ";
                    }

                    cout << flush;

                    //
                    // Avanzar tiempo
                    //
                    if (!pausado) {

                        tiempoActual++;
                    }

                    this_thread::sleep_for(
                        chrono::seconds(1)
                    );
                }

                //
                // Salir completamente
                //
                if (salir) {

                    cout
                        << "\nSaliendo de la reproduccion...\n";

                    listaReproduccion.vaciar();

                    Console::pause();

                    Console::clear();

                    break;
                }

                cout
                    << "\nTermino: "
                    << actual->getTitle()
                    << "\n";
            }

            //
            // Sacar de la cola
            //
            listaReproduccion.desencolar();
        }

        //
        // Mostrar historial
        //
        cout
            << "\n=======================================\n";

        cout
            << "Historial de reproduccion\n";

        cout
            << "=======================================\n";

        while (!historial.estaVacia()) {

            Multimedia* item =
                historial.obtenerTope();

            cout
                << "- "
                << item->getTitle()
                << "\n";

            historial.desapilar();
        }

        Console::pause();
    }
}