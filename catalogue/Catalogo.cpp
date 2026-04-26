#include "../algorithms/mergeSort.h"
#include "../catalogue/Catalogo.h"


Multimedia* Catalogo::find(const std::string& title) const {
    ListaMultiMedia* cur = head;
    while (cur) {
        if (cur->media && cur->media->getTitle() == title)
            return cur->media;
        cur = cur->next;
    }
    return nullptr;
}

ListaMultiMedia* Catalogo::get_general_recommendations() {
    ListaMultiMedia* sortedListByFavorites = this->head->copyList(this->head); // lista copiada, por eso es q en recomendados sale igual al mostrar lista

    mergeSort(&sortedListByFavorites, [](Multimedia* a, Multimedia* b) {
        return a->getCountFavorites() > b->getCountFavorites();
    });

    ListaMultiMedia* curr = sortedListByFavorites;
    int count = 0;
    while (curr != nullptr && curr->next != nullptr && count < 10) {
        curr = curr->next;
        count++;
    }
    //xd
    if (curr) curr->next = nullptr;

    return sortedListByFavorites;
}

/*esta funcion hace que ingreso el genero q quiero y me diante addFavorite hace que se le añada 1
 mas al favorito por lo tanto me recomiende ese*/
ListaMultiMedia* Catalogo::get_recommendations_by_genre(const std::string& genre) {

    ListaMultiMedia* filtered = nullptr;
    ListaMultiMedia* tailFiltered = nullptr;

    ListaMultiMedia* cur = head;

    //filtrar por genero
    while (cur) {
        if (cur->media && cur->media->getGenre() == genre) {

            ListaMultiMedia* nuevo = new ListaMultiMedia(
                cur->media->clone()
            );

            if (!filtered) {
                filtered = tailFiltered = nuevo;
            } else {
                tailFiltered->next = nuevo;
                nuevo->prev = tailFiltered;
                tailFiltered = nuevo;
            }
        }
        cur = cur->next;
    }

    //Si no hay nada
    if (!filtered) return nullptr;

    // Ordenar por favoritos
    mergeSort(&filtered, [](Multimedia* a, Multimedia* b) {
        return a->getCountFavorites() > b->getCountFavorites();
    });

    // solo el p´rimero
    if (filtered->next) {
        ListaMultiMedia* temp = filtered->next;
        filtered->next = nullptr;
        delete temp; 
    }

    return filtered;
}
