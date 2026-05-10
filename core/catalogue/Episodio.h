#pragma once
#include<string>

using namespace std;


class Episodio
{
private:
    int number;
    string tittle;
    int durMin;
public:
    Episodio(int num, string tit, int dur){
        number =num;
        tittle=tit;
        durMin=dur;
    }
    ~Episodio();

    int getNumber() const{return number;}
    string getTittle() const{return tittle;}
    int getDuration() const{return durMin;}
};


