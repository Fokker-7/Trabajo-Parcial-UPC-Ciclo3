#pragma once

#include "catalogue/Multimedia.h"

struct ListaMultiMedia {
    Multimedia* media;
    ListaMultiMedia* next;
    ListaMultiMedia* prev;

    ListaMultiMedia(Multimedia* m = nullptr)
        : media(m), next(nullptr), prev(nullptr) {}

    ~ListaMultiMedia() { delete media; }

    ListaMultiMedia* copyList(ListaMultiMedia* head) {
        if (!head) return nullptr;

        ListaMultiMedia* newHead = new ListaMultiMedia(
            head->media ? head->media->clone() : nullptr
        );

        ListaMultiMedia* curNew = newHead;
        ListaMultiMedia* curOld = head->next;

        while (curOld) {
            curNew->next = new ListaMultiMedia(
                curOld->media ? curOld->media->clone() : nullptr
            );

            curNew->next->prev = curNew;

            curNew = curNew->next;
            curOld = curOld->next;
        }

        return newHead;
    }
};