#pragma once

#include "structures/ListaMultiMedia.h"
#include <string>

class Catalogo {
public:
    Catalogo(const std::string& name = "")
        : head(nullptr), tail(nullptr), count(0), name(name) {}

    ~Catalogo() { clear(); }

    // No copy 
    Catalogo(const Catalogo&) = delete;
    Catalogo& operator=(const Catalogo&) = delete;

    // Añade una copia del multimedia al catálogo (usa clone())
    void add(const Multimedia& m) {
        Multimedia* copy = m.clone();
        ListaMultiMedia* node = new ListaMultiMedia(copy);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++count;
    }

    // Elimina el primer elemento con el título dado. Devuelve true si se eliminó.
    bool remove(const std::string& title) {
        ListaMultiMedia* cur = head;
        while (cur) {
            if (cur->media && cur->media->getTitle() == title) {
                if (cur->prev) cur->prev->next = cur->next;
                else head = cur->next;
                if (cur->next) cur->next->prev = cur->prev;
                else tail = cur->prev;
                delete cur;
                --count;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // Busca por título; devuelve puntero al objeto (no propietario)
    Multimedia* find(const std::string& title) const;

    ListaMultiMedia* get_general_recommendations();//funcion de copia??
    ListaMultiMedia* get_recommendations_by_genre(const std::string& genre);
    // Muestra información de todos los elementos (usa printInfo())
    void listAll() const {
        ListaMultiMedia* cur = head;
        while (cur) {
            if (cur->media) cur->media->printInfo();
            cur = cur->next;
        }
    }

    // Vacía el catálogo y libera memoria
    void clear() {
        ListaMultiMedia* cur = head;
        while (cur) {
            ListaMultiMedia* next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        count = 0;
    }
    
    std::size_t size() const { return count; }

    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

private:
    ListaMultiMedia* head;
    ListaMultiMedia* tail;
    std::size_t count;
    std::string name;
};
