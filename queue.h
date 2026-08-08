// Copyright (c) 2026 Nimul Islam Mahin and contributors
// SPDX-License-Identifier: MIT
// See the LICENSE file for details.

#include <iostream>
/**
 * Time Complexities:
 * - enqueue()       : O(1) - Constant time insertion at the rear.
 * - dequeue()       : O(n) - Linear time due to shifting elements after removal.
 * - frontElement()  : O(1) - Direct access to the first index.
 * - rearElement()   : O(1) - Direct access to the rear index.
 * - peek()          : O(1) - Direct access to a specific index.
 * - traverse()      : O(n) - Linear time to visit every element.
 * - isEmpty/isFull(): O(1) - Simple conditional checks.
 */
template <typename DataType>
class LinearQueue
{
public:
    LinearQueue(int size): rear(-1), size(size), data(new DataType[size]) {}

    ~LinearQueue()
    {
        delete[] this->data;
    }

private:
    int size;
    DataType *data = nullptr;
    int rear;

public:
    void enqueue(const DataType &data);
    DataType dequeue();
    DataType frontElement();
    DataType rearElement();
    DataType peek(int position);
    void traverse();
    bool isEmpty();
    bool isFull();
};


template <typename T>
bool LinearQueue<T>::isEmpty()
{
    if (this->rear == -1)
    {
        return true;
    }
    return false;
}


template <typename T>
bool LinearQueue<T>::isFull()
{
    if (this->rear == this->size - 1) 
    {
        return true;
    }
    return false;
}


template <typename T>
void LinearQueue<T>::enqueue(const T &data)
{
    if (this->isFull())
    {
        std::cout << "Queue is full!" << std::endl;
        return;
    }

    this->rear++;


    this->data[this->rear] = data;
}


template <typename T>
T LinearQueue<T>::dequeue()
{
 
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        return T(); 
    }
   
    T dequeued_element = this->data[0];

 
    for (int i = 0; i < this->rear; i++)
    {
        this->data[i] = this->data[i + 1];
    }
  
    this->rear--;
  
    return dequeued_element;
}


template <typename T>
T LinearQueue<T>::frontElement()
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        return T();
    }
    return this->data[0];
}


template <typename T>
T LinearQueue<T>::rearElement()
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        return T();
    }

    return this->data[this->rear]; 
}

template <typename T>
T LinearQueue<T>::peek(int position)
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        return T();
    }

    return this->data[position - 1]; 
}

template <typename T>
void LinearQueue<T>::traverse()
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        return;
    }

    for (int i = 0; i <= this->rear; i++) 
    {
        std::cout << "[" << i + 1 << "]: " << this->data[i] << std::endl;
    }
}

