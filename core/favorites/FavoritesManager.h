#pragma once

#include <vector>
#include <string>

#include "favorites/Favorite.h"
#include "catalogue/Catalogo.h"

class Persona;
class Multimedia;
class LogHandler;

class FavoriteManager {

private:

    std::vector<Favorite> favorites;

    std::string filename;

public:

    FavoriteManager(
        const std::string& filename
    );

    void load();

    void save();

    bool isFavorite(
        int userId,
        int mediaId
    ) const;

    void addFavorite(
        Persona* user,
        Multimedia* media,
        LogHandler& logger
    );

    std::vector<int> getFavoritesByUser(
        int userId
    ) const;
    void rehydrate(Catalogo& catalogo);
};