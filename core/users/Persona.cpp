#include "users/Persona.h"

Persona::Persona(
    int id,
    const std::string& username
)
    : id(id),
      username(username) {}

int Persona::getId() const {
    return id;
}

std::string Persona::getUsername() const {
    return username;
}