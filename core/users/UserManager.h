#pragma once

#include <vector>
#include <string>

#include "users/Persona.h"

class UserManager {
private:
    std::vector<Persona*> users;

    Persona* currentUser;

    std::string filename;

    int nextId;

public:
    UserManager(const std::string& filename);

    ~UserManager();

    void load();

    void save();

    void clear();

    bool registerUser(
        const std::string& username,
        const std::string& role
    );

    bool login(const std::string& username);

    void logout();
    bool isLoggedIn() const;
    bool usernameExists(
        const std::string& username
    ) const;

    Persona* getCurrentUser() const;

    void showUsers() const;
};
