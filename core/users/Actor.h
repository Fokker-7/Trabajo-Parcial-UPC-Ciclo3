#pragma once
#include "Persona.h"
#include "utils/Contacto.h"
#include <iostream>

class Actor : public Persona {
private:
    std::string papelPrincipal;
    Contacto contacto;

public:
    Actor(
        int id,
        const std::string& username,
        const std::string& papel,
        const Contacto& contacto
    )
    : Persona(id, username),
      papelPrincipal(papel),
      contacto(contacto) {}

    std::string getRole() const override {
        return "ACTOR";
    }

    void printInfo() const override {
        std::cout << "[Actor] " << getUsername()
                  << " | Papel: " << papelPrincipal << "\n"
                  << "           Contacto -> Email: " << contacto.getEmail()
                  << " | Tel: " << contacto.getPhone() << std::endl;
    }

    const std::string& getPapel() const { return papelPrincipal; }
};