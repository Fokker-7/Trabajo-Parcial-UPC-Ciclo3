#pragma once

#include "users/Persona.h"

class Usuario : public Persona {
public:
    Usuario(
        int id,
        const std::string& username
    );

    std::string getRole() const override;

    void printInfo() const override;
};