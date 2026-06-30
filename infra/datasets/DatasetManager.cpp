#include "datasetManager.h" 
#include "../../core/users/Actor.h"
#include "../../core/users/Director.h"
#include "../../core/catalogue/Pelicula.h"
#include "../../core/catalogue/Serie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

using namespace std;

datasetManager::~datasetManager(){
for (auto& pair : people) {
        delete pair.second;
    }
}

void datasetManager::loadPeople() {
    ifstream file("data/personas.csv");
    if (!file.is_open()) return;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, type, email, phone;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        int id = stoi(idStr);
        Contacto contacto(phone, email);

        if (type == "director") {
            people[id] = new Director(id, name, 0, contacto);
        } else {
            people[id] = new Actor(id, name, "Unknown", contacto);
        }
    }
    file.close();
}

void datasetManager::loadData(Catalogo& catalogo) {
    ifstream file("data/multimedia.csv");
    if (!file.is_open()) return;

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, title, genre, yearStr, durStr, type, dirIdStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, genre, ',');
        getline(ss, yearStr, ',');
        getline(ss, durStr, ',');
        getline(ss, type, ',');
        getline(ss, dirIdStr, ',');

        int id = stoi(idStr);
        int year = stoi(yearStr);
        int duration = stoi(durStr);
        int directorId = stoi(dirIdStr);

        Persona* director = people[directorId];
        vector<Persona*> actors;

        if (type == "pelicula") {
            catalogo.add(new Pelicula(id, title, genre, year, duration, director, actors));
        } else {
            catalogo.add(new Serie(id, title, genre, year, duration, director, actors));
        }
    }
    file.close();
}

void datasetManager::loadActors(Catalogo& catalogo) {
    ifstream file("data/media_actors.csv");
    if (!file.is_open()) return;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string mediaTitle, actorIdStr;

        getline(ss, mediaTitle, ',');
        getline(ss, actorIdStr, ',');

        int actorId = stoi(actorIdStr);
        Multimedia* media = catalogo.find(mediaTitle);

        if (media && people.count(actorId)) {
            media->addActor(people[actorId]);
        }
    }
    file.close();
}

void datasetManager::loadAll(Catalogo& catalogo){
    loadPeople();
    loadData(catalogo);
    loadActors(catalogo);
}

void datasetManager::generateMassiveData(int amount){
    ofstream file("data/multimedia.csv", ios::app);
    
    if (!file.is_open()) {
        cout << "Error al abrir multimedia.csv para generar datos.\n";
        return;
    }

    vector<string> adjetivos = {"Oscuro", "Letal", "Oculto", "Increible", "Ultimo", "Salvaje"};
    vector<string> sustantivos = {"Destino", "Pacto", "Viaje", "Heroe", "Misterio", "Guerrero"};
    vector<string> generos = {"Accion", "Drama", "Comedia", "Terror", "Ciencia Ficcion"};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distAdjetivo(0, adjetivos.size() - 1);
    uniform_int_distribution<> distSustantivo(0, sustantivos.size() - 1);
    uniform_int_distribution<> distGenero(0, generos.size() - 1);
    uniform_int_distribution<> distYear(1980, 2026);
    uniform_int_distribution<> distDuration(80, 180);
    uniform_int_distribution<> distDirector(1, people.size());

    int baseId = 1000;

    for (int i = 0; i < amount; i++) {
        string title = "El " + sustantivos[distSustantivo(gen)] + " " + adjetivos[distAdjetivo(gen)];
        string genre = generos[distGenero(gen)];
        int year = distYear(gen);
        int duration = distDuration(gen);
        string type = (i % 2 == 0) ? "pelicula" : "serie";
    int dirId = distDirector(gen);
    file << (baseId + i) << "," 
            << title << "," 
            << genre << "," 
            << year << "," 
            << duration << "," 
            << type << "," 
            << dirId << "\n";
    }

    file.close();
    cout<<"\nSe han generado "<<amount<<" peliculas exitosamente.\n";
}