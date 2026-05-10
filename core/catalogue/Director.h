#pragma once
#include "Contacto.h"
class Director
{
private:
    string nombre;
    int pelDirigidas;
    Contacto contacto;
public:
    Director(string nom, int pel, string p="", string e=""): nombre(nom), pelDirigidas(pel), contacto(p, e){}
    ~Director(){}

    string getNombre(){return nombre;}
    void printInfo(){
        cout<<"[Director] "<<nombre<< " | Obras dirigidas: "<< pelDirigidas<<endl;
        cout << "           Contacto -> Email: " << contacto.getEmail() 
         << " | Tel: " << contacto.getPhone() << endl;
    }
};

