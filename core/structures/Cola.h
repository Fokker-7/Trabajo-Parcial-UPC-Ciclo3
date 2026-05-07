#pragma once
#include <iostream>
#include <functional>

template <typename T>
class Cola {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T v) : dato(v), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* final;
    size_t cantidad;

public:
    Cola() : frente(nullptr), final(nullptr), cantidad(0) {}
    ~Cola() { vaciar(); }

    bool estaVacia() const { return cantidad == 0; }
    size_t size() const { return cantidad; }

    void encolar(T v) {
        Nodo* nuevo = new Nodo(v);
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        cantidad++;
    }

    void desencolar() {
        if (estaVacia()) return;
        Nodo* temp = frente;
        frente = frente->siguiente;
        if (!frente) final = nullptr;
        delete temp;
        cantidad--;
    }

    T obtenerFrente() const {
        if (estaVacia()) throw std::runtime_error("Cola vacía");
        return frente->dato;
    }

    void vaciar() {
        while (!estaVacia()) desencolar();
    }

    // Uso de Lambdas para procesar la cola sin vaciarla
    void procesar(std::function<void(T&)> accion) {
        Nodo* actual = frente;
        while (actual) {
            accion(actual->dato);
            actual = actual->siguiente;
        }
    }
};