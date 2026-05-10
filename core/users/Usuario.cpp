#include "users/Usuario.h"

#include <iostream>

Usuario::Usuario(
    int id,
    const std::string& username
)
    : Persona(id, username) {}

std::string Usuario::getRole() const {
    return "USER";
}

void Usuario::printInfo() const {

    std::cout
        << "[USER] "
        << username
        << "\n";
}