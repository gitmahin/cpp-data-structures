// Copyright (c) 2026 Nimul Islam Mahin and contributors
// SPDX-License-Identifier: MIT
// See the LICENSE file for details.

#pragma once
#include <iostream>

class Utils
{
public:
    template <std::size_t n>
    void printArray(int (&arr)[n]);
    void swap(int &a, int &b);
};

template <std::size_t n>
void Utils::printArray(int (&arr)[n])
{
    unsigned int size = std::size(arr);
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void Utils::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}