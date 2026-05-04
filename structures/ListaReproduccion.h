#include<iostream>

template <typename T>
class ListaReproduccion
{
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

    ListaReproduccion(){
        frente=nullptr;
        final=nullptr;
        cantidad=0;
    }
    ~ListaReproduccion(){}

    bool estaVacia() const { return cantidad == 0; }
    size_t size() const { return cantidad; }


    void encolar(T v){
        Nodo* nuevo= new Nodo(v);
            if (estaVacia())
            {
                frente=final=nuevo;
            }else{
                final->siguiente=nuevo;
                final=nuevo;
            }
        cantidad++;
    }

    void desencolar(){
        if (estaVacia()) return;
        Nodo*temp=frente;
        frente=frente->siguiente;

        if (frente==nullptr) final=nullptr;

        delete temp;
        cantidad--;
    }

    T obtenerFrente() const {
        if (estaVacia()) std::cout<<"\nLa lista de reproduccion esta vacia.\n";
        return frente->dato;
    }
    
    void vaciar(){
        while (!estaVacia())
        {
            desencolar();
        }
    }

    template<typename Accion>
    void procesar(Accion accion){
        Nodo* actual = frente;
        while (actual)
        {
            accion(actual->dato);
            actual= actual->siguiente;
        }
        
    }



};
