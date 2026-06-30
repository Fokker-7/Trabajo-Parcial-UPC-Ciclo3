#include <iostream>
#include "catalogue/Catalogo.h"
#include "structures/Cola.h"
#include "favorites/FavoritesManager.h"
#include "CatalogoUI.h"
#include "../infra/datasets/datasetManager.h"

using namespace std;

int main() {
    Catalogo catalogo("Mi catalogo multimedia");
    Cola<Multimedia*> listaReproduccion;

    datasetManager dataManager;
    dataManager.loadAll(catalogo);

    UserManager userManager("data/users.txt");
    FavoriteManager favoriteManager("data/favorites.txt");
    LogHandler logger("data/logs.txt");

    favoriteManager.rehydrate(catalogo);

    CatalogoUI ui(
        catalogo,
        listaReproduccion,
        userManager,
        logger,
        favoriteManager
    );

    ui.run();

    return 0;
}