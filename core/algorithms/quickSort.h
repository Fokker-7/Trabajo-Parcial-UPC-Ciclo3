#pragma once

#include <vector>
#include <utility>

//
// PARTITION
//
template <typename T, typename Compare>
int partition(
    std::vector<T>& arr,
    int low,
    int high,
    Compare comp
) {

    T pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (comp(arr[j], pivot)) {

            i++;

            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);

    return i + 1;
}

//
// QUICK SORT
//
template <typename T, typename Compare>
void quickSort(
    std::vector<T>& arr,
    int low,
    int high,
    Compare comp
) {

    if (low < high) {

        int pi = partition(
            arr,
            low,
            high,
            comp
        );

        quickSort(
            arr,
            low,
            pi - 1,
            comp
        );

        quickSort(
            arr,
            pi + 1,
            high,
            comp
        );
    }
}