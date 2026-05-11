#pragma once
#include <string>

class Contacto {
private:
    std::string phone;
    std::string email;

public:

    Contacto()
        : phone(""), email("") {}

    Contacto(
        const std::string& phone,
        const std::string& email
    )
        : phone(phone), email(email) {}

    const std::string& getPhone() const {
        return phone;
    }

    const std::string& getEmail() const {
        return email;
    }
};