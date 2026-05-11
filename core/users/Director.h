#pragma once
#include "Persona.h"
#include "utils/Contacto.h"
#include <iostream>

class Director : public Persona {
private:
    int pelDirigidas;
    Contacto contacto;

public:
    Director(
        int id,
        const std::string& username,
        int pelDirigidas,
        const Contacto& contacto
    )
    : Persona(id, username),
      pelDirigidas(pelDirigidas),
      contacto(contacto) {}

    std::string getRole() const override {
        return "DIRECTOR";
    }

    void printInfo() const override {
        std::cout << "[Director] " << getUsername()
                  << " | Obras dirigidas: " << pelDirigidas << "\n"
                  << "           Contacto -> Email: " << contacto.getEmail()
                  << " | Tel: " << contacto.getPhone() << std::endl;
    }

    int getPeliculasDirigidas() const {
        return pelDirigidas;
    }
};