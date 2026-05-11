#pragma once

template <typename T, typename Compare>
void heapify(T arr[], int n, int i, Compare comp) {

    int best = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && comp(arr[left], arr[best]))
        best = left;

    if (right < n && comp(arr[right], arr[best]))
        best = right;

    if (best != i) {
        std::swap(arr[i], arr[best]);
        heapify(arr, n, best, comp);
    }
}

template <typename T, typename Compare>
void heapSort(T arr[], int n, Compare comp) {

    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comp);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, comp);
    }
}