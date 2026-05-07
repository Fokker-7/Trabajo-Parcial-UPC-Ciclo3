#pragma once

#include "users/Persona.h"

class Admin : public Persona {
public:
    Admin(
        int id,
        const std::string& username
    );

    std::string getRole() const override;

    void printInfo() const override;
};