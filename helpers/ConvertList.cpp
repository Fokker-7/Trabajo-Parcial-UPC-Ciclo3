#include "ConvertList.h"

std::vector<Multimedia*> toVector(ListaMultiMedia* head) {
    std::vector<Multimedia*> items;

    auto cur = head;
    while (cur) {
        if (cur->media) {
            items.push_back(cur->media);
        }
        cur = cur->next;
    }

    return items;
}