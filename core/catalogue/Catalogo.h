#pragma once

#include "structures/ListaDoble.h"
#include "catalogue/Multimedia.h"
#include <string>

class Catalogo {
public:
    Catalogo(const std::string& name = "");
    ~Catalogo();

    Catalogo(const Catalogo&) = delete;
    Catalogo& operator=(const Catalogo&) = delete;

    void add(const Multimedia& m);

    bool remove(const std::string& title);

    Multimedia* find(const std::string& title) const;

    ListaDoble<Multimedia*>* get_general_recommendations();

    ListaDoble<Multimedia*>* get_recommendations_by_genre(
        const std::string& genre
    );

    ListaDoble<Multimedia*>* get_top_10();

    void listAll() const;

    void clear();

    std::size_t size() const;

    const std::string& getName() const;
    void setName(const std::string& n);

private:
    ListaDoble<Multimedia*> lista;
    std::string name;
};