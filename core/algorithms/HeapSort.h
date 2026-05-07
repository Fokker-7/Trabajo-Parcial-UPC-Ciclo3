#pragma once

template <typename T, typename Compare>
void heapify(T arr[], int n, int i, Compare comp){
    int bigger = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if (left<n && comp(arr[left], arr[bigger]))
    {
        bigger=left;
    }

    if (right<n && comp(arr[right], arr[bigger]))
    {
        bigger=right;
    }
    
    if (bigger!=i)
    {
        T temp = arr[i];
        arr[i]=arr[bigger];
        arr[bigger]= temp;

        heapify(arr, n, bigger, comp);
    }
}

template <typename T, typename Compare>
void heapSort(T arr[], int n, Compare comp){
    for (int i = n/2 -1; i>= 0; i--){
        T temp=arr[0];
        arr[0]= arr[i];
        arr[i]=temp;
        heapify (arr, i, 0, comp);
    }
}