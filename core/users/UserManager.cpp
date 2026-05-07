#include "users/UserManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "users/Usuario.h"
#include "users/Admin.h"

UserManager::UserManager(const std::string& filename)
    : currentUser(nullptr),
      filename(filename),
      nextId(1)
{
    load();
}

UserManager::~UserManager() {
    clear();
}

void UserManager::clear() {
    for (Persona* user : users) {
        delete user;
    }

    users.clear();
}

void UserManager::load() {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {

        std::stringstream ss(line);

        std::string idStr;
        std::string role;
        std::string username;

        std::getline(ss, idStr, '|');
        std::getline(ss, role, '|');
        std::getline(ss, username);

        int id = std::stoi(idStr);

        if (role == "ADMIN") {

            users.push_back(
                new Admin(id, username)
            );

        } else {

            users.push_back(
                new Usuario(id, username)
            );
        }

        if (id >= nextId) {
            nextId = id + 1;
        }
    }

    file.close();
}

void UserManager::save() {

    std::ofstream file(filename);

    if (!file.is_open()) {
        return;
    }

    for (Persona* user : users) {

        file
            << user->getId()
            << "|"
            << user->getRole()
            << "|"
            << user->getUsername()
            << "\n";
    }

    file.close();
}

void UserManager::registerUser(
    const std::string& username,
    const std::string& role
) {

    Persona* newUser = nullptr;

    if (role == "ADMIN") {

        newUser = new Admin(
            nextId,
            username
        );

    } else {

        newUser = new Usuario(
            nextId,
            username
        );
    }

    users.push_back(newUser);

    nextId++;

    save();
}   

bool UserManager::login(
    const std::string& username
) {

    for (Persona* user : users) {

        if (user->getUsername() == username) {

            currentUser = user;

            return true;
        }
    }

    return false;
}

void UserManager::logout() {
    currentUser = nullptr;
}

Persona* UserManager::getCurrentUser() const {
    return currentUser;
}

void UserManager::showUsers() const {

    for (Persona* user : users) {
        user->printInfo();
    }
}

