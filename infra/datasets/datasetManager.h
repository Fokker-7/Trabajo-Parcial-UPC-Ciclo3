#pragma once

#include "../../core/catalogue/Catalogo.h"
#include "../../core/users/Persona.h"
#include <unordered_map>
#include <string>

class datasetManager
{
private:
    std::unordered_map<int, Persona*> people;
public:
    datasetManager() = default;
    ~datasetManager();

    void loadPeople();
    void loadData(Catalogo& catalogo);
    void loadActors(Catalogo& catalogo);
    void loadAll(Catalogo& catalogo);
    void generateMassiveData(int amount);
};
