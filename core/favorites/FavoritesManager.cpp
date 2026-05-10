#include "favorites/FavoritesManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "users/Persona.h"
#include "catalogue/Multimedia.h"
#include "logs/LogHandler.h"

FavoriteManager::FavoriteManager(
    const std::string& filename
)
    : filename(filename)
{
    load();
}

void FavoriteManager::load() {

    std::ifstream file(filename);

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {

        std::stringstream ss(line);

        std::string userIdStr;
        std::string mediaIdStr;

        std::getline(ss, userIdStr, '|');
        std::getline(ss, mediaIdStr);

        favorites.push_back(
            Favorite(
                std::stoi(userIdStr),
                std::stoi(mediaIdStr)
            )
        );
    }

    file.close();
}

void FavoriteManager::save() {

    std::ofstream file(filename);

    if (!file.is_open()) {
        return;
    }

    for (const Favorite& fav : favorites) {

        file
            << fav.getUserId()
            << "|"
            << fav.getMediaId()
            << "\n";
    }

    file.close();
}

bool FavoriteManager::isFavorite(
    int userId,
    int mediaId
) const {

    for (const Favorite& fav : favorites) {

        if (
            fav.getUserId() == userId
            &&
            fav.getMediaId() == mediaId
        ) {
            return true;
        }
    }

    return false;
}

void FavoriteManager::addFavorite(
    Persona* user,
    Multimedia* media,
    LogHandler& logger
) {

    int userId =
        user->getId();

    int mediaId =
        media->getId();

    if (isFavorite(userId, mediaId)) {

        std::cout
            << "Ya esta en favoritos.\n";

        return;
    }

    favorites.push_back(
        Favorite(userId, mediaId)
    );

    media->addFavorite();

    save();

    logger.addLog(
        user->getUsername()
        + " agrego a favoritos: "
        + media->getTitle()
    );
}

std::vector<int>
FavoriteManager::getFavoritesByUser(
    int userId
) const {

    std::vector<int> result;

    for (const Favorite& fav : favorites) {

        if (fav.getUserId() == userId) {

            result.push_back(
                fav.getMediaId()
            );
        }
    }

    return result;
}