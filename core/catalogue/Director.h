#pragma once
#include <iostream>
#include <string>

using namespace std;

class Director
{
private:
    string nombre;
    int pelDirigidas;
public:
    Director(string nom, int pel){
        nombre=nom;
        pelDirigidas=pel;
    }
    ~Director();

    string getNombre(){return nombre;}
    void printInfo(){
        cout<<"[Director] "<<nombre<< " | Obras dirigidas: "<< pelDirigidas<<endl;
    }
};

