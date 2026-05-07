#include "ConvertList.h"

std::vector<Multimedia*> toVector(
    ListaDoble<Multimedia*>::Nodo* head
) {

    std::vector<Multimedia*> items;

    auto cur = head;

    while (cur) {

        if (cur->dato) {

            items.push_back(
                cur->dato
            );
        }

        cur = cur->next;
    }

    return items;
}