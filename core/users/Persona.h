#pragma once

#include <string>

class Persona {
protected:
    int id;
    std::string username;

public:
    Persona(
        int id,
        const std::string& username
    );

    virtual ~Persona() = default;

    int getId() const;
    std::string getUsername() const;

    virtual std::string getRole() const = 0;

    virtual void printInfo() const = 0;
};