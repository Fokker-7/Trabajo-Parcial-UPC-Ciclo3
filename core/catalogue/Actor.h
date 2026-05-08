#pragma once
#include <iostream>
#include <string>

using namespace std;

class Actor
{
private:
    string nombre;
    string papelPrincipal;
public:
    Actor(string nom, string papel){
        nombre=nom;
        papelPrincipal=papel;
    }
    ~Actor(){}

    string getNombre(){return nombre;}

    void printInfo(){
        cout<<"[Actor] "<< nombre<<" | Papel Destacado: "<<papelPrincipal;
    }
};

