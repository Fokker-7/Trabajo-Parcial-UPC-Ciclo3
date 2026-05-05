#include "CatalogoUI.h"
#include "reproductor/Reproductor.h"
#include "ConvertList.h"

#include <iostream>

using namespace std;

CatalogoUI::CatalogoUI(Catalogo& c, ListaReproduccion<Multimedia*>& l)
    : catalogo(c), lista(l) {}

void CatalogoUI::renderHome() {
    system("clear");

    cout << "========================================\n";
    cout << "        🎬 TU CATALOGO\n";
    cout << "========================================\n\n";

    cout << "🔥 TOP RECOMENDADOS\n";
    auto top = catalogo.get_general_recommendations();

    auto cur = top;
    while (cur) {
        cout << "[ " << cur->media->getTitle() << " ] ";
        cur = cur->next;
    }

    while (top) {
        auto temp = top;
        top = top->next;
        delete temp;
    }

    cout << "\n\n[1] Buscar   [2] Genero   [3] Lista  [4] Ver todo  [0] Salir\n";
}

void CatalogoUI::showSearch() {
    cin.ignore();
    cout << "Buscar titulo: ";
    string titulo;
    getline(cin, titulo);

    auto encontrado = catalogo.find(titulo);

    if (encontrado) encontrado->printInfo();
    else cout << "No encontrado\n";

    cin.get();
}

void CatalogoUI::showGenero() {
    cin.ignore();
    cout << "Genero: ";
    string genero;
    getline(cin, genero);

    auto rec = catalogo.get_recommendations_by_genre(genero);

    while (rec) {
        cout << "[ " << rec->media->getTitle() << " ] ";
        auto temp = rec;
        rec = rec->next;
        delete temp;
    }

    cin.get();
}

void CatalogoUI::showLista() {
    cout << "\n[1] Agregar\n[2] Reproducir\n";
    int op;
    cin >> op;

    if (op == 1) {
        cin.ignore();
        cout << "Titulo: ";
        string titulo;
        getline(cin, titulo);

        auto encontrado = catalogo.find(titulo);
        if (encontrado) {
            lista.encolar(encontrado);
            cout << "Agregado\n";
        }
    } else if (op == 2) {
        Reproductor::iniciar(lista);
    }
}

void CatalogoUI::run() {
    int opcion;

    do {
        renderHome();
        cout << "Seleccione: ";
        cin >> opcion;

        switch (opcion) {
            case 1: showSearch(); break;
            case 2: showGenero(); break;
            case 3: showLista(); break;
            case 4: showPaginated(catalogo.get_general_recommendations()); break;
        }

    } while (opcion != 0);
}

void CatalogoUI::showPaginated(ListaMultiMedia* head) {

    auto items = toVector(head);

    if (items.empty()) {
        cout << "No hay elementos.\n";
        cin.get();
        return;
    }

    int page = 0;
    int totalPages = (items.size() + PAGE_SIZE - 1) / PAGE_SIZE;

    while (true) {

        system("clear");

        cout << "========================================\n";
        cout << "        📚 CATALOGO (PAGINADO)\n";
        cout << "========================================\n\n";

        int start = page * PAGE_SIZE;
        int end = min(start + PAGE_SIZE, (int)items.size());

        for (int i = start; i < end; i++) {
            cout << "- " << items[i]->getTitle()
                 << " (" << items[i]->getYear() << ")\n";
        }

        cout << "\nPagina " << (page + 1) << "/" << totalPages << "\n";
        cout << "[N] Sig  [P] Ant  [Q] Salir\n";

        char c;
        cin >> c;

        if (c == 'N' || c == 'n') {
            if (page < totalPages - 1) page++;
        }
        else if (c == 'P' || c == 'p') {
            if (page > 0) page--;
        }
        else if (c == 'Q' || c == 'q') {
            break;
        }
    }
}