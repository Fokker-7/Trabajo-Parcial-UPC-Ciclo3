#pragma once

#include "catalogue/Catalogo.h"

#include "structures/Cola.h"

#include "catalogue/Multimedia.h"

const int PAGE_SIZE = 5;

class CatalogoUI {

private:

    Catalogo& catalogo;

    Cola<Multimedia*>& lista;

    void renderHome();

    void showSearch();

    void showGenero();

    void showLista();

    void showPaginated(
        ListaDoble<Multimedia*>* lista
    );

    void showTop10();

public:

    CatalogoUI(
        Catalogo& c,
        Cola<Multimedia*>& l
    );

    void run();
};