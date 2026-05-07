#include "Reproductor.h"
#include "../../infra/input/Keyboard.h"
#include "../../infra/utils/Console.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

namespace Reproductor {

    void iniciar(ListaReproduccion<Multimedia*>& listaReproduccion) {

        if (listaReproduccion.estaVacia()) {
            cout << "Tu lista de reproduccion esta vacia.\n";
            return;
        }

        cout << "Contenido en cola:\n";
        listaReproduccion.procesar([](Multimedia* m) {
            cout << " - " << m->getTitle()
                 << " (" << m->getYear() << ")\n";
        });

        auto imprimirTiempo = [](int totalSegundos) {
            int h = totalSegundos / 3600;
            int m = (totalSegundos % 3600) / 60;
            int s = totalSegundos % 60;

            cout << setfill('0') << setw(2) << h << ":"
                 << setw(2) << m << ":"
                 << setw(2) << s;
        };

        while (!listaReproduccion.estaVacia()) {

            Multimedia* actual = listaReproduccion.obtenerFrente();

            if (actual) {
                Console::clear();

                cout << "\n=======================================\n";
                cout << "Reproduciendo: " << actual->getTitle() << "\n";
                cout << "Controles: [P] Pausa/Reanudar, [S] Saltar, [Q] Salir";
                cout << "\n=======================================\n";

                int duracionSeg = actual->getDuration() * 60;
                int tiempoActual = 0;

                bool pausado = false;
                bool saltar = false;
                bool salir = false;

                while (tiempoActual <= duracionSeg && !saltar && !salir) {

                    if (Keyboard::kbhit()) {
                        char tecla = Keyboard::getch();

                        if (tecla == 'P' || tecla == 'p') pausado = !pausado;
                        if (tecla == 'S' || tecla == 's') saltar = true;
                        if (tecla == 'Q' || tecla == 'q') salir = true;
                    }

                    cout << "\r[";
                    imprimirTiempo(tiempoActual);
                    cout << "/";
                    imprimirTiempo(duracionSeg);
                    cout << "] ";

                    if (pausado) {cout << " [PAUSADO]  \r";}
                    else {cout << "                \r";}

                    cout << flush;

                    if (!pausado) tiempoActual++;

                    this_thread::sleep_for(chrono::seconds(1));
                }

                if (salir) {
                    cout << "\nSaliendo de la reproduccion...\n";
                    listaReproduccion.vaciar();
                    Console::pause();
                    Console::clear();
                    break;
                }

                cout << "\nTermino: " << actual->getTitle() << "\n";
            }

            listaReproduccion.desencolar();
        }
    }

}