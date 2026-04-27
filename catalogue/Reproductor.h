#pragma once
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <iomanip>
#include "Multimedia.h"
#include "../structures/ListaReproduccion.h"

using namespace std;

namespace Reproductor {
    void iniciar(ListaReproduccion<Multimedia*>& listaReproduccion) {

        if (listaReproduccion.estaVacia())
        {
            cout << "Tu lista de reproduccion esta vacia.\n";
            return;
        }

        cout << "Contenido en cola:\n";
        listaReproduccion.procesar([](Multimedia* m) {
            cout << " - " << m->getTitle() << " (" << m->getYear() << ")\n";
        });

        auto imprimirTiempo =[] (int totalSegundos) {
            int h= totalSegundos / 3600;
            int m= (totalSegundos % 3600) / 60;
            int s= totalSegundos % 60;
            cout << setfill('0') << setw(2) << h << ":" 
                 << setfill('0') << setw(2) << m << ":" 
                 << setfill('0') << setw(2) << s;
        };

        while (!listaReproduccion.estaVacia())
        {
            Multimedia* actual = listaReproduccion.obtenerFrente();
            if (actual)
            {
                system("cls");
                cout<<"\n=======================================\n";
                cout << "Reproduciendo: " << actual->getTitle() << "\n";
                cout<<"Controles: [P] Pausa/Reanudar, [S] Saltar, [Q] Salir";
                cout<<"\n=======================================\n";

                int duracion = actual->getDuration();
                int duracionSeg = duracion * 60;
                int minActual = 0;
                bool pausado = false;
                bool saltar = false;
                bool salir = false;

                while (minActual <=duracionSeg && !saltar && !salir)
                {
                    if (_kbhit())
                    {
                        char tecla= _getch();
                        if (tecla == 'P' || tecla == 'p') pausado = !pausado;
                        if (tecla == 'S' || tecla == 's') saltar = true;
                        if (tecla == 'Q' || tecla == 'q') salir = true;
                    }
                    
                    if (!pausado)
                    {
                        cout << "\r["; imprimirTiempo(minActual); cout<< "/"; imprimirTiempo(duracionSeg); cout<<"]           " <<flush;
                        minActual++;
                        this_thread::sleep_for(chrono::milliseconds(1000));
                    }else{
                        cout << "\r["; imprimirTiempo(minActual); cout<< "/"; imprimirTiempo(duracionSeg); cout<<"] [PAUSADO]"<<flush;
                        this_thread::sleep_for(chrono::milliseconds(1000));
                    }
                }
                 if (salir)
                {
                    cout << "\nSaliendo de la reproduccion...\n";
                    listaReproduccion.vaciar();
                    system("pause");
                    system("cls");
                    break;
                }
                    
                    cout<<"\n Termino: " << actual->getTitle() << "\n";
                    this_thread::sleep_for(chrono::milliseconds(1));
            }
          listaReproduccion.desencolar();

        }
        

        
    }
}