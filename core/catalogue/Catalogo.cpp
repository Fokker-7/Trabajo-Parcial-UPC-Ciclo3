#include "Catalogo.h"
#include "../algorithms/mergeSort.h"

Catalogo::Catalogo(const std::string& name)
    : name(name) {}

Catalogo::~Catalogo() {
    clear();
}

void Catalogo::add(const Multimedia& m) {
    lista.push_back(m.clone());
}

Multimedia* Catalogo::find(const std::string& title) const {

    auto nodo = lista.buscar([&](Multimedia* media) {
        return media &&
               media->getTitle() == title;
    });

    return nodo ? nodo->dato : nullptr;
}

void Catalogo::listAll() const {

    auto cur = lista.getHead();

    while (cur) {

        if (cur->dato)
            cur->dato->printInfo();

        cur = cur->next;
    }
}
Multimedia* Catalogo::findById(int id) {

    auto cur = lista.getHead();

    while (cur) {

        if (cur->dato && cur->dato->getId() == id) {
            return cur->dato;
        }

        cur = cur->next;
    }

    return nullptr;
}

void Catalogo::clear() {
    lista.clear();
}

std::size_t Catalogo::size() const {
    return lista.size();
}

const std::string& Catalogo::getName() const {
    return name;
}

void Catalogo::setName(const std::string& n) {
    name = n;
}

ListaDoble<Multimedia*>*
Catalogo::get_general_recommendations() {

    auto* copia =
        new ListaDoble<Multimedia*>();

    auto cur = lista.getHead();

    while (cur) {

        copia->push_back(
            cur->dato->clone()
        );

        cur = cur->next;
    }

    return copia;
}

ListaDoble<Multimedia*>*
Catalogo::get_recommendations_by_genre(
    const std::string& genre
) {

    auto* filtered =
        new ListaDoble<Multimedia*>();

    auto cur = lista.getHead();

    // Filtrar por género
    while (cur) {

        if (
            cur->dato &&
            cur->dato->getGenre() == genre
        ) {

            filtered->push_back(
                cur->dato->clone()
            );
        }

        cur = cur->next;
    }

    // Si no hay resultados
    if (filtered->size() == 0) {
        delete filtered;
        return nullptr;
    }

    // Ordenar por favoritos
    mergeSort<Multimedia*>(
        &filtered->getHeadRef(),
        [](Multimedia* a, Multimedia* b) {

            return a->getCountFavorites() >
                   b->getCountFavorites();
        }
    );

    filtered->rebuildTail();

    return filtered;
}