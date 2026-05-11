#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "catalogue/Pelicula.h"
#include "catalogue/Serie.h"

#include "users/Actor.h"
#include "users/Director.h"

#include "favorites/FavoritesManager.h"

#include "structures/Cola.h"

#include "CatalogoUI.h"

using namespace std;

unordered_map<int, Persona*> people;

//
// CARGAR PERSONAS
//
void loadPeople() {

    ifstream file("data/personas.csv");

    if (!file.is_open()) {
        cout << "No se pudo abrir personas.csv\n";
        return;
    }

    string line;

    getline(file, line);

    while (getline(file, line)) {

        if (line.empty())
            continue;

        stringstream ss(line);

        string idStr;
        string name;
        string type;
        string email;
        string phone;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        int id = stoi(idStr);

        if (type == "director") {
            Contacto contacto(phone, email);

            people[id] =
                new Director(
                    id,
                    name,
                    0,
                    contacto
                );
        } else {
            Contacto contacto(phone, email);

            people[id] =
                new Actor(
                id,
                name,
                "Unknown",
                contacto
            );
        }
    }

    file.close();
}

//
// CARGAR MULTIMEDIA
//
void loadData(Catalogo& catalogo) {

    ifstream file("data/multimedia.csv");

    if (!file.is_open()) {

        cout << "No se pudo abrir multimedia.csv\n";
        return;
    }

    string line;

    getline(file, line); // header

    while (getline(file, line)) {

        if (line.empty())
            continue;

        stringstream ss(line);

        string idStr;
        string title;
        string genre;
        string yearStr;
        string durationStr;
        string type;
        string directorIdStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, genre, ',');
        getline(ss, yearStr, ',');
        getline(ss, durationStr, ',');
        getline(ss, type, ',');
        getline(ss, directorIdStr, ',');

        int id = stoi(idStr);
        int year = stoi(yearStr);
        int duration = stoi(durationStr);
        int directorId = stoi(directorIdStr);

        Persona* director =
            people[directorId];

        vector<Persona*> actors;

        if (type == "pelicula") {

            catalogo.add(
                new Pelicula(
                    id,
                    title,
                    genre,
                    year,
                    duration,
                    director,
                    actors
                )
            );
        }
        else {

            catalogo.add(
                new Serie(
                    id,
                    title,
                    genre,
                    year,
                    duration,
                    director,
                    actors
                )
            );
        }
    }

    file.close();
}

//
// CARGAR ACTORES
//
void loadActors(Catalogo& catalogo) {

    ifstream file("data/media_actors.csv");

    if (!file.is_open()) {
        cout << "No se pudo abrir media_actors.csv\n";
        return;
    }

    string line;

    getline(file, line);

    while (getline(file, line)) {

        if (line.empty())
            continue;

        stringstream ss(line);

        string mediaTitle;
        string actorIdStr;

        getline(ss, mediaTitle, ',');
        getline(ss, actorIdStr, ',');

        int actorId = stoi(actorIdStr);

        Multimedia* media =
            catalogo.find(mediaTitle);

        if (media && people.count(actorId)) {

            media->addActor(
                people[actorId]
            );
        }
    }

    file.close();
}

int main() {

    Catalogo catalogo(
        "Mi catalogo multimedia"
    );

    Cola<Multimedia*> listaReproduccion;

    //
    // LOAD PIPELINE
    //
    loadPeople();

    loadData(catalogo);

    loadActors(catalogo);

    UserManager userManager(
        "data/users.txt"
    );

    FavoriteManager favoriteManager(
        "data/favorites.txt"
    );

    LogHandler logger(
        "data/logs.txt"
    );

    favoriteManager.rehydrate(catalogo);

    CatalogoUI ui(
        catalogo,
        listaReproduccion,
        userManager,
        logger,
        favoriteManager
    );

    ui.run();

    //
    // liberar personas
    //
    for (auto& pair : people) {
        delete pair.second;
    }

    return 0;
}