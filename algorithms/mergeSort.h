#include "../catalogue/Catalogo.h"

// Divide la lista en dos mitades
void split(
    ListaMultiMedia* head,
    ListaMultiMedia** first,
    ListaMultiMedia** second
) {

    ListaMultiMedia* slow = head;
    ListaMultiMedia* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *first = head;
    *second = slow->next;

    slow->next = nullptr;

    if (*second)
        (*second)->prev = nullptr;
}

template <typename Compare>
ListaMultiMedia* merge(
    ListaMultiMedia* a,
    ListaMultiMedia* b,
    Compare comp
) {

    if (!a) return b;
    if (!b) return a;

    ListaMultiMedia* result = nullptr;

    if (comp(a->media, b->media)) {
        result = a;
        result->next = merge(a->next, b, comp);
        if (result->next) result->next->prev = result;
    } else {
        result = b;
        result->next = merge(a, b->next, comp);
        if (result->next) result->next->prev = result;
    }

    result->prev = nullptr;
    return result;
}

template <typename Compare>
void mergeSort(ListaMultiMedia** headRef, Compare comp) {

    ListaMultiMedia* head = *headRef;

    if (!head || !head->next)
        return;

    ListaMultiMedia* a;
    ListaMultiMedia* b;

    split(head, &a, &b);

    mergeSort(&a, comp);
    mergeSort(&b, comp);

    *headRef = merge(a, b, comp);
}