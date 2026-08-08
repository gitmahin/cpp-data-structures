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
#include <string>

template <typename T>
class Stack
{
public:
    Stack(const int size) : size(size), top(-1), data(new T[size]) {};

    ~Stack()
    {
        delete[] this->data;
    }

    void push(const T &data);
    T pop();
    const bool isEmpty() const;
    const bool isFull() const;
    const T &htop() const;
    const int getSize() const;
    void traverse();

private:
    int top;
    int size;
    T *data;
};

template <typename T>
const bool Stack<T>::isEmpty() const
{
    if (this->top == -1)
    {
        return true;
    }

    return false;
}

template <typename T>
const bool Stack<T>::isFull() const
{
    if (this->top == this->size - 1)
    {
        return true;
    }
    return false;
}

template <typename T>
void Stack<T>::push(const T &data)
{

    if (!this->data)
    {
        std::cout << "Stack not created yet!" << std::endl;
        return;
    }

    if (this->isFull())
    {
        std::cout << "Stack Overflow!" << std::endl;
        return;
    }

    this->top++;
    this->data[this->top] = data;
}

template <typename T>
T Stack<T>::pop()
{

    if (!this->data)
    {
        std::cout << "Stack not created yet!" << std::endl;
        return T();
    }

    if (this->isEmpty())
    {
        std::cout << "Stack Underflow!" << std::endl;
        return T();
    }

    T data = this->data[this->top];
    this->top--;

    return data;
}

template <typename T>
const T &Stack<T>::htop() const
{

    if (!this->data)
    {
        std::cout << "Stack not created yet!" << std::endl;
        static const T empty{};
        return empty;
    }

    if (this->isEmpty())
    {
        std::cout << "Stack Underflow!" << std::endl;
        static const T empty{};
        return empty;
    }

    return this->data[this->top];
}

template <typename T>
const int Stack<T>::getSize() const
{
    return this->size;
}

template <typename T>
void Stack<T>::traverse()
{
    if (this->isEmpty())
    {
        std::cout << "Stack Underflow!" << std::endl;
        return;
    }
    for (int i = 0; i <= this->top; i++)
    {
        std::cout << this->data[this->top - i] << " ";
    }
    std::cout << std::endl;
}
