#pragma once
#include <iostream>
#include <functional>

template <typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T v) : dato(v), siguiente(nullptr) {}
    };

    Nodo* tope;
    size_t cantidad;

public:
    Pila() : tope(nullptr), cantidad(0) {}
    ~Pila() { limpiar(); }

    bool estaVacia() const { return tope == nullptr; }
    size_t size() const { return cantidad; }

    // Insertar 
    void apilar(T v) {
        Nodo* nuevo = new Nodo(v);
        nuevo->siguiente = tope;
        tope = nuevo;
        cantidad++;
    }

    // Eliminar
    void desapilar() {
        if (estaVacia()) return;
        Nodo* temp = tope;
        tope = tope->siguiente;
        delete temp;
        cantidad--;
    }

    // Peek
    T obtenerTope() const {
        if (estaVacia()) throw std::runtime_error("Pila vacía");
        return tope->dato;
    }

    void limpiar() {
        while (!estaVacia()) desapilar();
    }

    // Lambda para buscar si un elemento está en el historial
    bool contiene(std::function<bool(T)> criterio) {
        Nodo* actual = tope;
        while (actual) {
            if (criterio(actual->dato)) return true;
            actual = actual->siguiente;
        }
        return false;
    }
};