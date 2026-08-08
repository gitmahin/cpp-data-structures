// Copyright (c) 2026 Nimul Islam Mahin and contributors
// SPDX-License-Identifier: MIT
// See the LICENSE file for details.

#pragma once
#include <iostream>

class Utils
{
public:
    template <std::size_t n, typename T>
    void printArray(const T (&arr)[n]);

    template <typename T>
    void printArray(const T *arr, int size);

    template <typename T>
    void swap(T &a, T &b);
};

template <std::size_t n, typename T>
void Utils::printArray(const T (&arr)[n])
{
    unsigned int size = std::size(arr);
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Utils::printArray(const T *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Utils::swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}