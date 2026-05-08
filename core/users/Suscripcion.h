#pragma once
#include<string>

using namespace std;

class Suscripcion
{
private:
    string tipoPlan;
    double precMen;
    bool activa;
public:
    Suscripcion(string tipo, double prec){
        tipoPlan=tipo;
        precMen=prec;
        activa=true;
    }
    ~Suscripcion();

    string getTipo(){return tipoPlan;}
    bool isActiva(){return activa;}
    void cancelSuscripcion(){activa=false;}
};