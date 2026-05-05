#pragma once
#include "catalogue/Catalogo.h"
#include "structures/ListaReproduccion.h"
#include "catalogue/Multimedia.h"

const int PAGE_SIZE = 5;

class CatalogoUI {
private:
    Catalogo& catalogo;
    ListaReproduccion<Multimedia*>& lista;

    void renderHome();
    void showSearch();
    void showGenero();
    void showLista();
    void showPaginated(ListaMultiMedia* head);

public:
    CatalogoUI(Catalogo& c, ListaReproduccion<Multimedia*>& l);

    void run();
};