#pragma once

#include "structures/ListaDoble.h"

//
// SPLIT
//
template <typename T>
void split(
    typename ListaDoble<T>::Nodo* head,
    typename ListaDoble<T>::Nodo** first,
    typename ListaDoble<T>::Nodo** second
) {

    using Nodo = typename ListaDoble<T>::Nodo;

    Nodo* slow = head;
    Nodo* fast = head->next;

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

//
// MERGE
//
template <typename T, typename Compare>
typename ListaDoble<T>::Nodo* merge(
    typename ListaDoble<T>::Nodo* a,
    typename ListaDoble<T>::Nodo* b,
    Compare comp
) {

    using Nodo = typename ListaDoble<T>::Nodo;

    if (!a) return b;
    if (!b) return a;

    Nodo* result = nullptr;

    if (comp(a->dato, b->dato)) {

        result = a;

        result->next = merge<T>(
            a->next,
            b,
            comp
        );

        if (result->next)
            result->next->prev = result;

    } else {

        result = b;

        result->next = merge<T>(
            a,
            b->next,
            comp
        );

        if (result->next)
            result->next->prev = result;
    }

    result->prev = nullptr;

    return result;
}

//
// MERGE SORT
//
template <typename T, typename Compare>
void mergeSort(
    typename ListaDoble<T>::Nodo** headRef,
    Compare comp
) {

    using Nodo = typename ListaDoble<T>::Nodo;

    Nodo* head = *headRef;

    if (!head || !head->next)
        return;

    Nodo* a;
    Nodo* b;

    split<T>(head, &a, &b);

    mergeSort<T>(&a, comp);
    mergeSort<T>(&b, comp);

    *headRef = merge<T>(a, b, comp);
}