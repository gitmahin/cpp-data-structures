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
};


template <std::size_t n>
void Sort::bubbleSort(int (&arr)[n])
{
    unsigned int size = std::size(arr);
    int temp_element;
    bool is_sorted = true;

    Utils utils;

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

