// Copyright (c) 2026 Nimul Islam Mahin and contributors
// SPDX-License-Identifier: MIT
// See the LICENSE file for details.

#pragma once

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG == 1
#ifndef LOG
#define LOG(x) std::cout << x << std::endl;
#endif
#else
#ifndef LOG
#define LOG(x)
#endif
#endif

#include <iostream>
#include "utils.h"

class Sort
{
public:
    template <std::size_t n>
    void bubbleSort(int (&arr)[n]);

    template <std::size_t n>
    void insertionSort(int (&arr)[n]);

    template <std::size_t n>
    void selectionSort(int (&arr)[n]);
};

template <std::size_t n>
void Sort::bubbleSort(int (&arr)[n])
{
    Utils utils;
    unsigned int size = std::size(arr);

    bool is_sorted = true;

    for (int i = 0; i < size - 1; i++)
    {
        is_sorted = true;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                utils.swap(arr[j], arr[j + 1]);
                is_sorted = false;
            }
        }
        if (is_sorted)
            return;
    }
}

template <std::size_t n>
void Sort::insertionSort(int (&arr)[n])
{
    Utils utils;
    unsigned int size = std::size(arr);
    int key, j;

    for (int i = 1; i <= size - 1; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <std::size_t n>
void Sort::selectionSort(int (&arr)[n])
{
    Utils utils;
    int min_index;
    unsigned int size = std::size(arr);

    for (int i = 0; i < size; i++)
    {
        min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        utils.swap(arr[i], arr[min_index]);
    }
}