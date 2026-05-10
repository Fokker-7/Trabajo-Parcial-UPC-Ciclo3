#pragma once
#include "Contacto.h"

class Actor
{
private:
    string nombre;
    string papelPrincipal;
    Contacto contacto;
public:
    Actor(string nom, string papel, string p="", string e=""): nombre(nom), papelPrincipal(papel), contacto(p, e){}
    ~Actor(){}

    string getNombre(){return nombre;}

    void printInfo(){
        cout<<"[Actor] "<< nombre<<" | Papel Destacado: "<<papelPrincipal;
        cout << "           Contacto -> Email: " << contacto.getEmail() 
         << " | Tel: " << contacto.getPhone() << endl;
    }
};

