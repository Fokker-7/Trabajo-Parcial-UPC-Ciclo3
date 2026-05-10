#pragma once
#include<string>

using namespace std;

class Favorito
{
private:
    string idMultimedia;
    string fechaAgregado;
public:
    Favorito(string id, string fecha){
    idMultimedia=id;
    fechaAgregado=fecha;
    } 
    ~Favorito();

    string getIdMultimedia() const{return idMultimedia;}
    string getFecha(){ return fechaAgregado;}
};
