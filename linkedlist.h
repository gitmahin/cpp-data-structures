// Copyright (c) 2026 Nimul Islam Mahin and contributors
// SPDX-License-Identifier: MIT
// See the LICENSE file for details.

#pragma once

#include <iostream>
#include <iomanip>

#define DEBUG 0

#if DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

namespace
{
    template <typename DataType>
    class ILinkedList
    {
    public:
        virtual bool isEmpty() = 0;

        virtual void traverse() = 0;
        virtual DataType peek(int position) = 0;

        int size = 0;

        virtual void insertAtStart(const DataType &data) = 0;
        virtual void insertAtEnd(const DataType &data) = 0;
        virtual void insertAtPosition(const DataType &data, int pos) = 0;

        virtual DataType deleteAtStart() = 0;
        virtual DataType deleteAtEnd() = 0;
        virtual DataType deleteAtPosition(int pos) = 0;
    };
}

namespace LinkedList
{

    /* -------------------------------------------------------------------------- */
    /*                            Singly Linked List                              */
    /* -------------------------------------------------------------------------- */
    template <typename DataType>
    class Singly : protected ILinkedList<DataType>
    {
    public:
        Singly<DataType> *singlyHead = nullptr;

        bool isEmpty() override;

        DataType peek(int position) override;
        void traverse() override;

        void insertAtStart(const DataType &data) override;
        void insertAtEnd(const DataType &data) override;
        void insertAtPosition(const DataType &data, int pos) override;

        DataType deleteAtStart() override;
        DataType deleteAtEnd() override;
        DataType deleteAtPosition(int pos) override;

        int getSize()
        {
            return this->size;
        }

    private:
        DataType data;
        Singly<DataType> *next;
    };

    template <typename T>
    bool Singly<T>::isEmpty()
    {
        // The list is considered empty if the singlyHead pointer does not reference a node on the heap.
        if (this->singlyHead == nullptr)
        {
            return true;
        }

        return false;
    }

    template <typename T>
    T Singly<T>::peek(int pos)
    {

        if (this->isEmpty())
        {
            LOG("Empty Singular Linked List!");
            return T();
        }

        int index = pos - 1;
        if (index < 0)
        {
            LOG("Invalid peek position");
            return T();
        }

        // Initialize a pointer for list traversal, starting at the singlyHead.
        Singly<T> *ptr = this->singlyHead;

        for (int i = 0; i < index && ptr->next != nullptr; i++)
        {
            LOG("peeking...");
            ptr = ptr->next;
        }

        return ptr->data;
    }

    template <typename T>
    void Singly<T>::traverse()
    {
        if (this->isEmpty())
        {
            LOG("Empty Singular Linked List!");
            return;
        }

        Singly<T> *ptr = this->singlyHead;

        int i = 0;

#if DEBUG
        std::cout << "+-------------+" << "\n";
        std::cout << "| Serial      | Data" << "\n";
        std::cout << "+-------------+" << "\n";
#endif
        while (ptr != nullptr)
        {
#if DEBUG
            std::cout << "| "
                      << std::setw(11) << i + 1
                      << " | "
                      << ptr->data
                      << std::endl;
#else
            std::cout << ptr->data << " ";
#endif

            ptr = ptr->next;
            i++;
        }
#if DEBUG
        std::cout << "+-------------+\n";
#else
        std::cout << std::endl;
#endif
    }

    template <typename T>
    void Singly<T>::insertAtStart(const T &data)
    {
        // Allocate a new node on the heap
        Singly<T> *newNode = new Singly<T>;
        // Initialize the new node's data
        newNode->data = data;
        // Point the new node to the current singlyHead
        newNode->next = this->singlyHead;
        // Reassign the singlyHead pointer to the new starting node
        this->singlyHead = newNode;
        this->size++;
    }

    template <typename T>
    void Singly<T>::insertAtPosition(const T &data, int pos)
    {
        int index = pos - 1;
        // If index is not the head node
        if (index >= 1 && !this->isEmpty())
        {
            Singly<T> *newNode = new Singly<T>;
            newNode->data = data;

            Singly<T> *ptr = this->singlyHead;

            int i = 0;
            while (i != index - 1 && ptr->next != nullptr)
            {
                ptr = ptr->next;
                i++;
            }

            newNode->next = ptr->next;
            ptr->next = newNode;
            this->size++;
            return;
        }

        // if index is head node than run insert at start with given data
        // By this way it won't throw [Segmentation fault(core dumped)] error
        this->insertAtStart(data);
    }

    template <typename T>
    void Singly<T>::insertAtEnd(const T &data)
    {
        if (this->isEmpty())
        {
            this->insertAtStart(data);
            return;
        }

        Singly<T> *newNode = new Singly<T>;
        newNode->data = data;
        newNode->next = nullptr;
        Singly<T> *ptr = this->singlyHead;
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
        this->size++;
        return;
    }

    template <typename T>
    T Singly<T>::deleteAtStart()
    {
        if (this->isEmpty())
        {
            LOG("Empty Singular Linked List!");
            return T();
        }

        // Save the singlyHead pointer so we can delete the node after unlinking it
        Singly<T> *removedNode = this->singlyHead;
        // Shift singlyHead to the next node; if singlyHead was the only element, it becomes nullptr
        this->singlyHead = this->singlyHead->next;
        // Buffer the data to return it after the node's memory is freed
        T removed_data = removedNode->data;
        // Prevent memory leaks by deallocating the removed node from the heap
        delete removedNode;
        this->size--;
        // Return the extracted data
        return removed_data;
    }

    template <typename T>
    T Singly<T>::deleteAtEnd()
    {

        if (this->isEmpty())
        {
            LOG("Empty Singular Linked List!");
            return T();
        }

        Singly<T> *p = this->singlyHead;
        Singly<T> *q = this->singlyHead->next;

        if (q != nullptr)
        {
            while (q->next != nullptr)
            {
                p = p->next;
                q = q->next;
            }

            p->next = nullptr;
            T removed_data = q->data;
            delete q;
            this->size--;
            return removed_data;
        }

        T removed_data = p->data;
        delete p;
        this->singlyHead = nullptr;
        this->size--;
        return removed_data;
    }

    template <typename T>
    T Singly<T>::deleteAtPosition(int pos)
    {
        int index = pos - 1;
        if (this->isEmpty())
        {
            LOG("Empty Singular Linked List!");
            return T();
        }

        Singly<T> *p = this->singlyHead;
        Singly<T> *q = this->singlyHead->next;

        if (index >= 1 && q != nullptr)
        {
            for (int i = 0; i < index - 1 && q->next != nullptr; i++)
            {
                p = p->next;
                q = q->next;
            }

            p->next = q->next;

            T removed_data = q->data;
            delete q;
            // Return this function. Otherwise it will run deletion for begin
            // element.
            this->size--;
            return removed_data;
        }

        // if head node then run delete at start
        // By this way it won't throw [Segmentation fault(core dumped)] error
        return this->deleteAtStart();
    }

    /* -------------------------------------------------------------------------- */
    /*                            Circular Linked List                            */
    /* -------------------------------------------------------------------------- */
    template <typename DataType>
    class Circular : protected ILinkedList<DataType>
    {
    public:
        Circular<DataType> *circularHead = nullptr;

        bool isEmpty() override;

        DataType peek(int position) override;
        void traverse() override;

        void insertAtStart(const DataType &data) override;
        void insertAtEnd(const DataType &data) override;
        void insertAtPosition(const DataType &data, int pos) override;

        DataType deleteAtStart() override;
        DataType deleteAtEnd() override;
        DataType deleteAtPosition(int pos) override;

    private:
        DataType data;
        Circular<DataType> *next;
    };

    template <typename T>
    bool Circular<T>::isEmpty()
    {
        // The list is considered empty if the circularHead pointer does not reference a node on the heap.
        if (this->circularHead == nullptr)
        {
            return true;
        }

        return false;
    }

    template <typename T>
    void Circular<T>::traverse()
    {
        if (this->isEmpty())
        {
            LOG("Empty Circular Linked List!");
            return;
        }

        Circular<T> *ptr = this->circularHead;

#if DEBUG

        std::cout << "+-------------+" << "\n";
        std::cout << "| Serial      | Data" << "\n";
        std::cout << "+-------------+" << "\n";
#endif
        int i = 0;
        do
        {
#if DEBUG
            std::cout << "| "
                      << std::setw(11) << i + 1
                      << " | "
                      << ptr->data
                      << std::endl;
#else
            std::cout << ptr->data << " ";
#endif

            ptr = ptr->next;
            i++;
        } while (ptr != this->circularHead);

#if DEBUG
        std::cout << "+-------------+\n";
#else
        std::cout << std::endl;
#endif
    }

    template <typename T>
    void Circular<T>::insertAtStart(const T &data)
    {
        Circular<T> *newNode = new Circular<T>;
        newNode->data = data;

        if (this->isEmpty())
        {
            this->circularHead = newNode;
            this->size++;
            this->circularHead->next = newNode;
            return;
        }

        Circular<T> *oldHead = this->circularHead;
        Circular<T> *ptr = this->circularHead;

        while (ptr->next != this->circularHead)
        {
            ptr = ptr->next;
        };

        ptr->next = newNode;
        newNode->next = oldHead;
        this->circularHead = newNode;
        this->size++;
    }

    template <typename T>
    T Circular<T>::peek(int pos)
    {
        return T();
    }

    template <typename T>
    void Circular<T>::insertAtPosition(const T &data, int pos)
    {
        int index = pos - 1;
        if (index >= 1 && !this->isEmpty())
        {
            Circular<T> *newNode = new Circular<T>;
            Circular<T> *ptr = this->circularHead;
            newNode->data = data;

            // You can use while here. I just used this loop and feeling Lazy to
            // delete, copy, write and .....
            for (int i = 0; i < index - 1 && ptr->next != this->circularHead; i++)
            {
                ptr = ptr->next;
            }

            newNode->next = ptr->next;
            ptr->next = newNode;
            this->size++;

            return;
        }

        this->insertAtStart(data);
    }

    template <typename T>
    void Circular<T>::insertAtEnd(const T &data)
    {
        if (this->isEmpty())
        {
            this->insertAtStart(data);
            return;
        }

        Circular<T> *newNode = new Circular<T>;

        newNode->data = data;

        Circular<T> *ptr = this->circularHead;

        while (ptr->next != this->circularHead)
        {
            ptr = ptr->next;
        };

        ptr->next = newNode;
        newNode->next = this->circularHead;
        this->size++;
    }

    template <typename T>
    T Circular<T>::deleteAtStart()
    {

        if (this->isEmpty())
        {
            LOG("Empty Circular Linked List!");
            return T();
        }

        Circular<T> *headToDelete = this->circularHead;
        Circular<T> *secondNode = headToDelete->next;
        Circular<T> *ptr = this->circularHead;

        T removed_data = headToDelete->data;

        if (ptr->next == this->circularHead)
        {
            delete headToDelete;
            this->circularHead = nullptr;
            this->size--;
            return removed_data;
        }

        while (ptr->next != this->circularHead)
        {
            ptr = ptr->next;
        };

        ptr->next = secondNode;
        this->circularHead = secondNode;

        delete headToDelete;
        this->size--;
        return removed_data;
    }

    template <typename T>
    T Circular<T>::deleteAtEnd()
    {

        if (this->isEmpty())
        {
            LOG("Empty Circular Linked List!");
            return T();
        }

        Circular *p = this->circularHead;
        Circular *q = this->circularHead->next;

        if (p->next == this->circularHead)
        {
            return this->deleteAtStart();
        }

        while (q->next != this->circularHead)
        {
            p = p->next;
            q = q->next;
        };

        p->next = this->circularHead;

        T removed_data = q->data;
        delete q;
        return removed_data;
    }

    template <typename T>
    T Circular<T>::deleteAtPosition(int pos)
    {

        int index = pos - 1;
        if (this->isEmpty())
        {
            LOG("Empty Circular Linked List!");
            return T();
        }

        Circular *p = this->circularHead;
        Circular *q = this->circularHead->next;

        if (index >= 1 && q != p)
        {

            for (int i = 0; i < index - 1 && q->next != p; i++)
            {
                p = p->next;
                q = q->next;
            }

            p->next = q->next;
            T removed_data = q->data;

            delete q;

            // Return this function. Otherwise it will run deletion for begin
            // element.
            this->size--;
            return removed_data;
        }

        return this->deleteAtStart();
    }

}