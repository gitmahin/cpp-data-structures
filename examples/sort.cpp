#include <iostream>
#include "../sort.h"

int main()
{
    int arr[] = {42, 7, 91, 15, 63, 28, 3, 77, 50, 19};

    Sort sort;
    Utils utils;

    std::cout << "Before sort:" << std::endl;
    utils.printArray(arr);
    sort.bubbleSort(arr);
    std::cout << "After Bubble sort:" << std::endl;
    utils.printArray(arr);

    sort.insertionSort(arr);
    std::cout << "After Insertion sort:" << std::endl;
    utils.printArray(arr);

    sort.selectionSort(arr);
    std::cout << "After Selection sort:" << std::endl;
    utils.printArray(arr);
}