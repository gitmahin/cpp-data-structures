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

template <typename T>
class Array
{
public:
    Array(int capacity) : capacity(capacity), rear(-1), data(new T[capacity]) {};

    const T *getData() const;
    const int getSize() const;
    bool isFull();
    bool isEmpty();
    void push(T data);
    void insertAt(T data, int pos);
    void insertAtStart(T data);
    void fill(T data);
    T deleteAt(int pos);
    T deleteAtEnd();
    T deleteAtStart();

    ~Array()
    {
        delete[] this->data;
    }

private:
    T *data;
    int capacity;
    int rear;
};

template <typename T>
bool Array<T>::isFull()
{
    if (this->rear == this->capacity - 1)
        return true;

    return false;
}

template <typename T>
bool Array<T>::isEmpty()
{
    if (this->rear == -1)
        return true;

    return false;
}

template <typename T>
void Array<T>::push(T data)
{
    if (this->isFull())
    {
        std::cout << "Array is full" << std::endl;
        return;
    }

    this->rear++;
    this->data[this->rear] = data;
}

template <typename T>
const T *Array<T>::getData() const
{
    return this->data;
}

template <typename T>
const int Array<T>::getSize() const
{
    return this->rear + 1;
}

template <typename T>
void Array<T>::insertAtStart(T data)
{

    if (this->isFull())
    {
        std::cout << "Array is full" << std::endl;
        return;
    }

    for (int i = this->rear; i >= 0; i--)
    {
        this->data[i + 1] = this->data[i];
    }
    this->rear++;
    this->data[0] = data;
}

template <typename T>
void Array<T>::insertAt(T data, int pos)
{
    const int index = pos - 1;

    if (this->isFull())
    {
        std::cout << "Array is full" << std::endl;
        return;
    }

    if (index <= 0)
    {
        this->insertAtStart(data);
        return;
    }

    for (int i = this->rear; i >= index; i--)
    {
        this->data[i + 1] = this->data[i];
    }
    this->rear++;
    if (index > this->rear)
        this->data[this->rear] = data;
    else
        this->data[index] = data;
    return;
}

template <typename T>
T Array<T>::deleteAtStart()
{
    if (this->isEmpty())
    {
        std::cout << "Array is already empty!" << std::endl;
        return T();
    }

    T temp_data = this->data[0];
    const int size = this->getSize();
    for (int i = 1; i <= size - 1; i++)
    {
        this->data[i - 1] = this->data[i];
    }

    this->rear--;
    return temp_data;
}

template <typename T>
T Array<T>::deleteAtEnd()
{

    if (this->isEmpty())
    {
        std::cout << "Array is already empty!" << std::endl;
        return T();
    }

    T temp_data = this->data[this->rear];
    this->rear--;
    return temp_data;
}

template <typename T>
T Array<T>::deleteAt(int pos)
{

    if (this->isEmpty())
    {
        std::cout << "Array is already empty!" << std::endl;
        return T();
    }

    int index = pos - 1;
    index = index <= 0 ? 0 : index > this->rear ? this->rear
                                                : index;

    T temp_data = this->data[index];

    if (index == 0)
    {
        this->deleteAtStart();
        return temp_data;
    }

    for (int i = index; i < this->rear; i++)
    {
        this->data[i] = this->data[i + 1];
    }

    this->rear--;
    return temp_data;
}

template <typename T>
void Array<T>::fill(T data)
{
    while (!this->isFull())
    {
        this->push(data);
    }
}