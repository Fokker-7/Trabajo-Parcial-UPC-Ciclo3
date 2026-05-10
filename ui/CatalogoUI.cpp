#include "CatalogoUI.h"

#include "reproductor/Reproductor.h"

#include "ConvertList.h"

#include <iostream>

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

    system("clear");

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

        << "[5] Login\n"
        << "[6] Registrarse\n"
        << "[7] Favoritos\n"

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

        system("clear");

        encontrado->printInfo();

        cout
            << "\n\n"

            << "[1] Agregar a favoritos\n"

            << "[2] Agregar a cola\n"

            << "[0] Volver\n";

        int op;

        cin >> op;

        switch (op) {

            //
            // Favoritos
            //
            case 1: {

                if (!userManager.isLoggedIn()) {

                    cout
                        << "\nDebes iniciar sesion.\n";

                    cin.ignore();

                    cin.get();

                    return;
                }

                favoriteManager.addFavorite(
                    userManager.getCurrentUser(),
                    encontrado,
                    logger
                );

                cout
                    << "\nAgregado a favoritos.\n";

                cin.ignore();

                cin.get();

                break;
            }

            //
            // Cola
            //
            case 2: {

                lista.encolar(encontrado);

                logger.addLog(
                    "Se agrego a cola: "
                    + encontrado->getTitle()
                );

                cout
                    << "\nAgregado a cola.\n";

                cin.ignore();

                cin.get();

                break;
            }
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

    if (!rec) {

        cout
            << "No hay recomendaciones\n";

        cin.get();

        return;
    }

    auto cur = rec->getHead();

    while (cur) {

        cout
            << "[ "
            << cur->dato->getTitle()
            << " ] ";

        cur = cur->next;
    }

    delete rec;

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
                showLogin();
                break;

            case 6:
                showRegister();
                break;

            case 7:
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

    cout << "\n🔥 TUS FAVORITOS\n\n";

    for (int id : favIds) {

        auto media = catalogo.findById(id);

        if (media) {

            media->printInfo();
        }
    }

    cin.ignore();
    cin.get();
}

void CatalogoUI::showPaginated(
    ListaDoble<Multimedia*>* lista
) {

    auto items =
        toVector(lista->getHead());

    if (items.empty()) {

        cout << "No hay elementos.\n";

        cin.get();

        return;
    }

    int page = 0;

    int totalPages =
        (items.size() + PAGE_SIZE - 1)
        / PAGE_SIZE;

    while (true) {

        system("clear");

        cout << "========================================\n";
        cout << "        📚 CATALOGO (PAGINADO)\n";
        cout << "========================================\n\n";

        int start =
            page * PAGE_SIZE;

        int end =
            min(
                start + PAGE_SIZE,
                (int)items.size()
            );

        for (int i = start; i < end; i++) {

            cout
                << "- "
                << items[i]->getTitle()
                << " ("
                << items[i]->getYear()
                << ")\n";
        }

        cout
            << "\nPagina "
            << (page + 1)
            << "/"
            << totalPages
            << "\n";

        cout
            << "[N] Sig  [P] Ant  [Q] Salir\n";

        char c;

        cin >> c;

        if (c == 'N' || c == 'n') {

            if (page < totalPages - 1)
                page++;
        }
        else if (c == 'P' || c == 'p') {

            if (page > 0)
                page--;
        }
        else if (c == 'Q' || c == 'q') {

            break;
        }
    }
}