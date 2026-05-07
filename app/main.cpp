#include <iostream>
#include <fstream>
#include <sstream>

#include "catalogue/Catalogo.h"

#include "catalogue/Pelicula.h"
#include "catalogue/Serie.h"

#include "catalogue/Multimedia.h"

#include "structures/Cola.h"

#include "CatalogoUI.h"

using namespace std;

void loadData(Catalogo& catalogo) {

    ifstream file("data/catalogo.csv");

    if (!file.is_open()) {

        cout
            << "No se pudo abrir catalogo.csv\n";

        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        string title;
        string genre;
        string type;

        int year;
        int duration;

        getline(ss, title, ',');

        getline(ss, genre, ',');

        ss >> year;

        ss.ignore();

        ss >> duration;

        ss.ignore();

        getline(ss, type, ',');

        //
        // Factory simple segun tipo
        //
        if (type == "pelicula") {

            catalogo.add(
                Pelicula(
                    title,
                    genre,
                    year,
                    duration
                )
            );
        }
        else if (type == "serie") {

            catalogo.add(
                Serie(
                    title,
                    genre,
                    year,
                    duration
                )
            );
        }
    }

    file.close();
}

int main() {

    //
    // Core del sistema
    //
    Catalogo catalogo(
        "Mi catalogo multimedia"
    );

    //
    // Cola FIFO de reproduccion
    //
    Cola<Multimedia*> listaReproduccion;

    //
    // Cargar data inicial
    //
    loadData(catalogo);

    //
    // UI Layer
    //
    CatalogoUI ui(
        catalogo,
        listaReproduccion
    );

    //
    // Arrancar app
    //
    ui.run();

    return 0;

};