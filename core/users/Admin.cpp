#include "users/Admin.h"

#include <iostream>

Admin::Admin(
    int id,
    const std::string& username
)
    : Persona(id, username) {}

std::string Admin::getRole() const {
    return "ADMIN";
}

void Admin::printInfo() const {

    std::cout
        << "[ADMIN] "
        << username
        << "\n";
}