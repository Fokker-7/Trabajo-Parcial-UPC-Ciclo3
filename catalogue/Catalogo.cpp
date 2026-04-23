#include "../algorithms/mergeSort.h"

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
    ListaMultiMedia* sortedListByFavorites = this->head->copyList(this->head);

    mergeSort(&sortedListByFavorites, [](ListaMultiMedia* a, ListaMultiMedia* b) {
        return a->media->getCountFavorites() > b->media->getCountFavorites();
    });

    ListaMultiMedia* curr = sortedListByFavorites;
    int count = 0;
    while (curr != nullptr && curr->next != nullptr && count < 10) {
        curr = curr->next;
        count++;
    };

    curr->next = nullptr;
    return sortedListByFavorites;
}