#pragma once
#include <iostream>
#include <string>

using namespace std;

class Contacto
{
private:
    string phone;
    string email;
public:
    Contacto(){
        phone="";
        email="";
    }

    Contacto(string p, string e){
        phone=p;
        email=e;
    }
    ~Contacto(){}

    string getPhone(){return phone;}
    string getEmail(){return email;}
};
