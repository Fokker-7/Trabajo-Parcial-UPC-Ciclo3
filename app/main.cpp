#include <iostream>
#include <fstream>
#include <sstream>

#include "catalogue/Catalogo.h"
#include "catalogue/Pelicula.h"
#include "catalogue/Serie.h"

#include "reproductor/Reproductor.h"
#include "CatalogoUI.h"

using namespace std;

void loadData(Catalogo& catalogo) {
    std::ifstream file("data/catalogo.csv");

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string title, genre, type;
        int year, duration;

        std::getline(ss, title, ',');
        std::getline(ss, genre, ',');
        ss >> year;
        ss.ignore();
        ss >> duration;
        ss.ignore();
        std::getline(ss, type, ',');

        if (type == "pelicula") {
            catalogo.add(Pelicula(title, genre, year, duration));
        } else {
            catalogo.add(Serie(title, genre, year, duration));
        }
    }
}

int main() {

    // 1. Core del sistema
    Catalogo catalogo("Mi catálogo");
    ListaReproduccion<Multimedia*> listaReproduccion;

    // 2. Datos iniciales
    loadData(catalogo);

    // 3. UI layer
    CatalogoUI ui(catalogo, listaReproduccion);

    // 4. Arrancar app
    ui.run();

    return 0;
}