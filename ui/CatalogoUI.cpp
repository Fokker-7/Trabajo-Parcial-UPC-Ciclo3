#include "CatalogoUI.h"

#include "reproductor/Reproductor.h"

#include "ConvertList.h"

#include <iostream>

#include "../infra/utils/Console.h"

using namespace std;

CatalogoUI::CatalogoUI(
    Catalogo& c,
    Cola<Multimedia*>& l,
    UserManager& um,
    LogHandler& logger,
    FavoriteManager& fm
)
    : catalogo(c),
      lista(l), userManager(um), logger(logger), favoriteManager(fm) {};

void CatalogoUI::renderHome() {

    Console::clear();

    if (userManager.isLoggedIn()) {
        cout << "👤 Usuario: "
            << userManager.getCurrentUser()->getUsername()
            << "\n";
    }
    else {
        cout << "👤 Invitado (login para más funciones)\n";
    }

    cout << "========================================\n";
    cout << "        🎬 TU CATALOGO\n";
    cout << "========================================\n\n";

    cout << "🔥 TOP RECOMENDADOS\n";

    auto* top =
        catalogo.get_general_recommendations();

    if (!top) {
        cout << "No hay recomendaciones.\n";

        return;
    }

    auto cur = top->getHead();

    while (cur) {

        if (!cur->dato) {
            break;
        }

        cout
            << "[ "
            << cur->dato->getTitle()
            << " ] ";

        cur = cur->next;
    }

    delete top;

    cout
        << "\n\n"

        << "[1] Buscar\n"

        << "[2] Genero\n"

        << "[3] Lista de reproduccion\n"

        << "[4] Ver todo\n"

        << "[5] Top 10 favoritos\n"
        << "[6] Login\n"
        << "[7] Registrarse\n"
        << "[8] Favoritos\n"

        << "[0] Salir\n";
}

void CatalogoUI::showSearch() {

    cin.ignore();

    cout << "Buscar titulo: ";

    string titulo;

    getline(cin, titulo);

    auto encontrado =
        catalogo.find(titulo);

    if (encontrado) {

        Console::clear();

        cout << "[1] Ver detalle\n";
        cout << "[2] Vista rapida\n";
        cout << "[0] Volver\n";

        int op;
        cin >> op;

        switch (op) {

            case 1:
                showMediaDetail(encontrado);
                break;

            case 2:
                encontrado->printInfo();
                cin.ignore();
                cin.get();
                break;
        }
    }
    else {

        cout << "No encontrado\n";

        cin.ignore();

        cin.get();
    }
}

void CatalogoUI::showLogin() {

    cin.ignore();

    string username;

    cout << "Username: ";
    getline(cin, username);

    if (userManager.login(username)) {

        logger.addLog(username + " inició sesión");

        cout << "Login exitoso\n";
    }
    else {

        cout << "Usuario no encontrado\n";
    }

    cin.get();
}

void CatalogoUI::showRegister() {

    cin.ignore();

    string username;

    cout << "Nuevo username: ";
    getline(cin, username);

    if (userManager.registerUser(username, "USER")) {

        logger.addLog(username + " se registró");

        cout << "Usuario creado.\n";
    }
    else {

        cout << "Username ocupado.\n";
    }

    cin.get();
}

void CatalogoUI::showGenero() {

    cin.ignore();

    cout << "Genero: ";

    string genero;

    getline(cin, genero);

    auto* rec =
        catalogo.get_recommendations_by_genre(
            genero
        );

    if (!rec || rec->size()==0) {

        cout
            << "No se encontraron resultados\n";
        cout
            << "Presione Enter para continuar\n";

        cin.get();

        return;
    }

    cout
        <<" Resultados para "<<genero<<": \n";

    auto cur = rec->getHead();

    while (cur) {

        cout
            << "[ "
            << cur->dato->getTitle()
            << " ] \n";

        cur = cur->next;
    }

    delete rec;

    cout
        << "Presione Enter para continuar\n";

    cin.get();
}

void CatalogoUI::showLista() {

    if (!userManager.isLoggedIn()) {

        cout << "\nDebes iniciar sesión para usar la lista.\n";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n"
         << "[1] Agregar a cola\n"
         << "[2] Reproducir cola\n";

    int op;
    cin >> op;

    if (op == 1) {

        cin.ignore();

        cout << "Titulo: ";

        string titulo;
        getline(cin, titulo);

        auto encontrado =
            catalogo.find(titulo);

        if (encontrado) {

            lista.encolar(encontrado);

            logger.addLog(
                userManager.getCurrentUser()->getUsername()
                + " agregó a cola: "
                + encontrado->getTitle()
            );

            cout << "Agregado a cola.\n";
        }
        else {
            cout << "No encontrado.\n";
        }

        cin.get();
    }

    else if (op == 2) {

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

            case 1:
                showSearch();
                break;

            case 2:
                showGenero();
                break;

            case 3:
                showLista();
                break;

            case 4: {

                auto* lista =
                    catalogo.get_general_recommendations();

                showPaginated(lista);

                delete lista;

                break;
            }
            case 5:
                
                showTop10();
                break;

            case 6:
                showLogin();
                break;

            case 7:
                showRegister();
                break;

            case 8:
                showFavorites();
                break;
        }

    } while (opcion != 0);
}

void CatalogoUI::showFavorites() {

    if (!userManager.isLoggedIn()) {

        cout << "\nDebes iniciar sesión.\n";
        cin.ignore();
        cin.get();
        return;
    }

    auto user = userManager.getCurrentUser();

    auto favIds =
        favoriteManager.getFavoritesByUser(user->getId());

    if (favIds.empty()) {

        cout << "\nNo tienes favoritos aún.\n";
        cin.ignore();
        cin.get();
        return;
    }

    while (true) {

        Console::clear();

        cout << "\n🔥 TUS FAVORITOS\n\n";

        int index = 1;
        std::vector<Multimedia*> items;

        for (int id : favIds) {

            auto media = catalogo.findById(id);

            if (media) {
                cout << index << ". " << media->getTitle() << "\n";
                items.push_back(media);
                index++;
            }
        }

        cout << "\n--------------------------------\n";
        cout << "[NUM] Ver detalle\n";
        cout << "[0] Volver\n";
        cout << "--------------------------------\n";
        cout << "Seleccion: ";

        int op;
        cin >> op;

        if (op == 0) return;

        if (op > 0 && op <= (int)items.size()) {
            items[op - 1]->printDetail();
            cout << "\nEnter para volver...";
            cin.ignore();
            cin.get();
        }
    }
}

void CatalogoUI::showPaginated(
    ListaDoble<Multimedia*>* lista
) {

    auto items = toVector(lista->getHead());

    if (items.empty()) {
        cout << "No hay elementos.\n";
        cin.get();
        return;
    }

    int page = 0;
    int totalPages = (items.size() + PAGE_SIZE - 1) / PAGE_SIZE;

    while (true) {

        Console::clear();

        cout << "========================================\n";
        cout << "        📚 CATALOGO (PAGINADO)\n";
        cout << "========================================\n\n";

        int start = page * PAGE_SIZE;
        int end = min(start + PAGE_SIZE, (int)items.size());

        for (int i = start; i < end; i++) {
            cout << (i - start + 1) << ". "
                 << items[i]->getTitle()
                 << " (" << items[i]->getYear() << ")\n";
        }

        cout << "\n----------------------------------------\n";
        cout << "[NUM] Ver detalle\n";
        cout << "[N] Siguiente pagina\n";
        cout << "[P] Pagina anterior\n";
        cout << "[Q] Salir\n";
        cout << "----------------------------------------\n";

        cout << "Seleccion: ";

        string input;
        cin >> input;

        // SALIR
        if (input == "q" || input == "Q")
            break;

        // SIGUIENTE
        else if (input == "n" || input == "N") {
            if (page < totalPages - 1) page++;
        }

        // ANTERIOR
        else if (input == "p" || input == "P") {
            if (page > 0) page--;
        }

        // DETALLE POR NUMERO
        else {
            try {
                int num = stoi(input);
                int index = start + (num - 1);

                if (index >= start && index < end) {
                    showMediaDetail(items[index]);
                }

            } catch (...) {
                cout << "\nEntrada invalida.\n";
                cin.ignore();
                cin.get();
            }
        }
    }
}

void CatalogoUI::showTop10() {

    while (true) {

        Console::clear();

        cout << "========================================\n";
        cout << "        🏆 TOP 10 FAVORITOS\n";
        cout << "========================================\n\n";

        auto items = catalogo.get_top_10();

        if (items.empty()) {
            cout << "No hay contenido suficiente para armar el top.\n";

            cout << "\nPresione Enter para volver...";
            cin.ignore();
            cin.get();
            return;
        }

        for (size_t i = 0; i < items.size(); i++) {

            cout << (i + 1) << ". "
                 << items[i]->getTitle()
                 << " (" << items[i]->getCountFavorites()
                 << " favs)\n";
        }

        cout << "\n--------------------------------\n";
        cout << "[NUM] Ver detalle\n";
        cout << "[0] Volver\n";
        cout << "--------------------------------\n";
        cout << "Seleccion: ";

        int op;
        cin >> op;

        if (op == 0)
            return;

        if (op > 0 && op <= (int)items.size()) {

            Console::clear();

            items[op - 1]->printDetail();

            cout << "\nEnter para volver...";
            cin.ignore();
            cin.get();
        }
    }
}

void CatalogoUI::showMediaDetail(Multimedia* media) {

    if (!media) return;

    Console::clear();

    media->printDetail();

    cout << "\n\n";

    cout << "[1] Agregar a favoritos\n";
    cout << "[2] Agregar a cola\n";
    cout << "[0] Volver\n";

    int op;
    cin >> op;

    switch (op) {

        case 1: {

            if (!userManager.isLoggedIn()) {

                cout << "\nDebes iniciar sesión.\n";
                cin.ignore();
                cin.get();
                return;
            }

            favoriteManager.addFavorite(
                userManager.getCurrentUser(),
                media,
                logger
            );

            cout << "\nAgregado a favoritos.\n";
            cin.ignore();
            cin.get();

            break;
        }

        case 2: {

            lista.encolar(media);

            logger.addLog(
                "Se agrego a cola: " + media->getTitle()
            );

            cout << "\nAgregado a cola.\n";
            cin.ignore();
            cin.get();

            break;
        }
    }
}