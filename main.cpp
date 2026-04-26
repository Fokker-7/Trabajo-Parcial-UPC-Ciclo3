#include <iostream>
#include "catalogue/Catalogo.h"
#include "catalogue/Pelicula.h"
#include "catalogue/Serie.h"
#include "catalogue/Catalogo.cpp"
#include "structures/ListaReproduccion.h"

using namespace std;

void mostrarLista(ListaMultiMedia* head) {
    ListaMultiMedia* cur = head;
    while (cur) {
        if (cur->media)
            cur->media->printInfo();
        cur = cur->next;
    }
}

int main() {
    Catalogo catalogo("Mi catálogo");

    ListaReproduccion<Multimedia*> listaReproduccion;

    Pelicula p1("Matrix", "ciencia ficcion", 1999, 120);
    Pelicula p4("Terminator", "ciencia ficcion", 1999, 120);

    Pelicula p2("Avengers", "accion", 2012, 140);
    Serie s1("Breaking Bad", "drama", 2008, 50);
    Serie s2("Dexter", "Drama", 2017, 45);
    p1.addFavorite();
    p1.addFavorite(); 
    catalogo.add(p1);
    catalogo.add(p2);
    catalogo.add(s1);
    catalogo.add(s2);
    catalogo.add(p4);

    int opcion;
    int xd;

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Mostrar todo el catalogo\n";
        cout << "2. Buscar por titulo\n";
        cout << "3. Recomendaciones top favoritos(global)\n";
        cout << "4. Recomendacion por genero\n";
        cout << "5. Agregar a lista de reproduccion\n"; //Cola
        cout << "6. Reproducir mi lista y vaciar\n"; //Desencolar
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

        //solo muestra la lista lisall
        case 1:
            cout << "\n=== CATALOGO ===\n";
            catalogo.listAll();
            break;

        //busca por titulo y muestra la info de ese titulo
        case 2: {
            cout << "Ingrese titulo: ";
            cin.ignore();
            string titulo;
            getline(cin, titulo);

            Multimedia* encontrado = catalogo.find(titulo);

            if (encontrado) {
                cout << "\nEncontrado:\n";
                encontrado->printInfo();
            } else {
                cout << "No encontrado\n";
            }
            break;
        }
        //recomendados pero por ahora la lista esta copiada de catalogo por eso sale igual a mostrar lista, pero si le dan favoritos a alguno y luego van a recomendados ese va a salir primero
        case 3: {
            cout << "\n=== TOP RECOMENDADOS ===\n";

            ListaMultiMedia* top = catalogo.get_general_recommendations();
            mostrarLista(top);
            while (top) {
                ListaMultiMedia* temp = top;
                top = top->next;
                delete temp;
            }
            //:v
            break;
        }
        //esta te busca quien esta primero en el genero
        case 4: {
            cout << "Ingrese genero: ";
            cin.ignore();
            string genero;
            getline(cin, genero);

            ListaMultiMedia* rec = catalogo.get_recommendations_by_genre(genero);

            if (!rec) {
                cout << "No hay recomendaciones para ese genero\n";
            } else {
                cout << "\nRecomendado:\n";
                mostrarLista(rec);

                while (rec) {
                    ListaMultiMedia* temp = rec;
                    rec = rec->next;
                    delete temp;
                }
            }
            break;
        }
case 5: {
            cout << "Ingrese titulo para agregar a lista de reproduccion: ";
            cin.ignore();
            string titulo;
            getline(cin, titulo);

            Multimedia* encontrado = catalogo.find(titulo);

            if (encontrado) {
                listaReproduccion.encolar(encontrado);
                cout << "Agregado a lista de reproduccion\n";
            } else {
                cout << "No encontrado\n";
            }
            break;
        }
case 6:{
            cout<<"\n=====Mi lista de reproduccion=========\n";
            if (listaReproduccion.estaVacia()) {
                cout << "Tu lista de reproduccion esta vacia.\n";
            } else {
               cout << "Contenido en cola:\n";
                listaReproduccion.procesar([](Multimedia* m) {
                    cout << " - " << m->getTitle() << " (" << m->getGenre() << ")\n";
                });
                cout << "--------------------------------------\n";

                while (!listaReproduccion.estaVacia()) {
                    Multimedia* actual = listaReproduccion.obtenerFrente();
                    if (actual) {
                        cout << "Reproduciendo: " << actual->getTitle() << "\n";
                        actual->printInfo();
                    }
                    listaReproduccion.desencolar();
                }
            }
         break;

        }
        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);

    return 0;
}

