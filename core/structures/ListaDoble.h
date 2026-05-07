#pragma once
#include <functional>

template <typename T>
class ListaDoble {
public:
    struct Nodo {
        T dato;
        Nodo* next;
        Nodo* prev;
        Nodo(T v) : dato(v), next(nullptr), prev(nullptr) {}
    };

private:
    Nodo* head;
    Nodo* tail;
    size_t count;

public:
    ListaDoble() : head(nullptr), tail(nullptr), count(0) {}
    
    ~ListaDoble() { clear(); }

    ListaDoble(const ListaDoble&) = delete;

    ListaDoble& operator=(
        const ListaDoble&
    ) = delete;

    // Agregar al final (O(1))
    void push_back(T v) {
        Nodo* nuevo = new Nodo(v);
        if (!head) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            nuevo->prev = tail;
            tail = nuevo;
        }
        count++;
    }

    void rebuildTail() {
        tail = head;

        while (tail && tail->next)
            tail = tail->next;
    }

    void setHead(Nodo* h) {
        head = h;
        rebuildTail();
    }

    // Método con Lambda para buscar (Punto B de la rúbrica)
    Nodo* buscar(std::function<bool(T)> criterio) const {
        Nodo* temp = head;
        while (temp) {
            if (criterio(temp->dato)) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    // Método con Lambda para filtrar/procesar
    void recorrer(std::function<void(T)> accion) {
        Nodo* temp = head;
        while (temp) {
            accion(temp->dato);
            temp = temp->next;
        }
    }

    void clear() {
        Nodo* cur = head;

        while (cur) {

            Nodo* next = cur->next;

            delete cur->dato;
            delete cur;

            cur = next;
        }

        head = tail = nullptr;
        count = 0;
    }

    size_t size() const { return count; }
    Nodo* getHead() const { return head; }
    Nodo*& getHeadRef() {
        return head;
    }
};