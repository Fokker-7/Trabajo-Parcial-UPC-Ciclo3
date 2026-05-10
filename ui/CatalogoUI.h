#pragma once

#include "catalogue/Catalogo.h"

#include "structures/Cola.h"

#include "catalogue/Multimedia.h"
#include "users/UserManager.h"
#include "logs/LogHandler.h"
#include "favorites/FavoritesManager.h"

const int PAGE_SIZE = 5;

class CatalogoUI {

private:

    Catalogo& catalogo;

    Cola<Multimedia*>& lista;
    UserManager& userManager;
    LogHandler& logger;
    FavoriteManager& favoriteManager;

    void renderHome();

    void showSearch();

    void showGenero();

    void showLista();

    void showPaginated(
        ListaDoble<Multimedia*>* lista
    );

    void showTop10();
    void showLogin();
    void showRegister();
    void showFavorites();

public:

    CatalogoUI(
        Catalogo& c,
        Cola<Multimedia*>& l,
        UserManager& um,
        LogHandler& logger,
        FavoriteManager& fm
    );

    void run();
};