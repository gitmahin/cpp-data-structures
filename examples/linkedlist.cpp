#include <iostream>
#include "../linkedlist.h"
#include <string>

void printHeader(const std::string &title)
{
    std::cout << "\n=== " << title << " ===\n";
}

void singlyDemo()
{
    printHeader("SINGLY LINKED LIST DEMO");

    LinkedList::Singly<int> list;

    std::cout << "isEmpty() -> " << std::boolalpha << list.isEmpty() << "\n";

    // insertAtStart: build 30 -> 20 -> 10
    list.insertAtStart(10);
    list.insertAtStart(20);
    list.insertAtStart(30);
    std::cout << "After insertAtStart(10), insertAtStart(20), insertAtStart(30): ";
    list.traverse(); // 30 20 10

    // insertAtEnd: append 40
    list.insertAtEnd(40);
    std::cout << "After insertAtEnd(40): ";
    list.traverse(); // 30 20 10 40

    // insertAtPosition: insert 25 at position 2
    list.insertAtPosition(25, 2);
    std::cout << "After insertAtPosition(25, pos=2): ";
    list.traverse(); // 30 25 20 10 40

    std::cout << "getSize() -> " << list.getSize() << "\n";
    std::cout << "peek(1) -> " << list.peek(1) << "  (head)\n";
    std::cout << "peek(3) -> " << list.peek(3) << "\n";

    // deleteAtStart
    int removed = list.deleteAtStart();
    std::cout << "deleteAtStart() removed " << removed << " -> ";
    list.traverse(); // 25 20 10 40

    // deleteAtEnd
    removed = list.deleteAtEnd();
    std::cout << "deleteAtEnd() removed " << removed << " -> ";
    list.traverse(); // 25 20 10

    // deleteAtPosition
    removed = list.deleteAtPosition(2);
    std::cout << "deleteAtPosition(2) removed " << removed << " -> ";
    list.traverse(); // 25 10

    std::cout << "getSize() -> " << list.getSize() << "\n";

    // Drain the list to show isEmpty() behavior
    while (!list.isEmpty())
    {
        list.deleteAtStart();
    }
    std::cout << "After draining all nodes, isEmpty() -> " << list.isEmpty() << "\n";
}

void circularDemo()
{
    printHeader("CIRCULAR LINKED LIST DEMO");

    LinkedList::Circular<std::string> list;

    std::cout << "isEmpty() -> " << std::boolalpha << list.isEmpty() << "\n";

    // insertAtStart: build C -> B -> A (each insertAtStart puts new node at head)
    list.insertAtStart("A");
    list.insertAtStart("B");
    list.insertAtStart("C");
    std::cout << "After insertAtStart(\"A\"), insertAtStart(\"B\"), insertAtStart(\"C\"): ";
    list.traverse(); // C B A

    // insertAtEnd: append D
    list.insertAtEnd("D");
    std::cout << "After insertAtEnd(\"D\"): ";
    list.traverse(); // C B A D

    // insertAtPosition: insert X at position 2
    list.insertAtPosition("X", 2);
    std::cout << "After insertAtPosition(\"X\", pos=2): ";
    list.traverse(); // C X B A D

    std::cout << "getSize() -> " << list.getSize() << "\n";

    // deleteAtStart
    std::string removed = list.deleteAtStart();
    std::cout << "deleteAtStart() removed \"" << removed << "\" -> ";
    list.traverse(); // X B A D

    // deleteAtEnd
    removed = list.deleteAtEnd();
    std::cout << "deleteAtEnd() removed \"" << removed << "\" -> ";
    list.traverse(); // X B A

    // deleteAtPosition
    removed = list.deleteAtPosition(2);
    std::cout << "deleteAtPosition(2) removed \"" << removed << "\" -> ";
    list.traverse(); // X A

    std::cout << "getSize() -> " << list.getSize() << "\n";

    // Drain the list to show isEmpty() behavior
    while (!list.isEmpty())
    {
        list.deleteAtStart();
    }
    std::cout << "After draining all nodes, isEmpty() -> " << list.isEmpty() << "\n";
}

int main()
{
    singlyDemo();
    circularDemo();
    return 0;
}