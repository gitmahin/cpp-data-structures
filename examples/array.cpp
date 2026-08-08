#include <iostream>
#include "../array.h"
#include "../utils.h"

int main()
{
    Utils utils;
    const unsigned int CAPACITY = 10;
    Array<int> arr(CAPACITY);

    // ---------- CREATE ----------
    std::cout << "=== Created Array (capacity 10) ===" << std::endl;
    std::cout << "isEmpty: " << std::boolalpha << arr.isEmpty() << std::endl;
    std::cout << std::endl;

    // ---------- PUSH ----------
    std::cout << "=== Pushing 23, 24, 25, 26, 27 ===" << std::endl;
    arr.push(23);
    arr.push(24);
    arr.push(25);
    arr.push(26);
    arr.push(27);

    utils.printArray(arr.getData(), arr.getSize());
    std::cout << "size: " << arr.getSize() << std::endl;
    std::cout << std::endl;

    // ---------- INSERT AT START ----------
    std::cout << "=== insertAtStart(99) ===" << std::endl;
    arr.insertAtStart(99);
    utils.printArray(arr.getData(), arr.getSize());
    std::cout << std::endl;

    // ---------- INSERT AT POSITION ----------
    // pos is 1-indexed; inserting at position 3 puts it between existing 2nd and 3rd elements
    std::cout << "=== insertAt(555, pos=3) ===" << std::endl;
    arr.insertAt(555, 3);
    utils.printArray(arr.getData(), arr.getSize());
    std::cout << std::endl;

    // ---------- DELETE AT START ----------
    std::cout << "=== deleteAtStart() ===" << std::endl;
    int deletedStart = arr.deleteAtStart();
    std::cout << "deleted value: " << deletedStart << std::endl;
    utils.printArray(arr.getData(), arr.getSize());
    std::cout << std::endl;

    // ---------- DELETE AT END ----------
    std::cout << "=== deleteAtEnd() ===" << std::endl;
    int deletedEnd = arr.deleteAtEnd();
    std::cout << "deleted value: " << deletedEnd << std::endl;
    utils.printArray(arr.getData(), arr.getSize());
    std::cout << std::endl;

    // ---------- DELETE AT POSITION ----------
    std::cout << "=== deleteAt(pos=2) ===" << std::endl;
    int deletedAt = arr.deleteAt(2);
    std::cout << "deleted value: " << deletedAt << std::endl;
    utils.printArray(arr.getData(), arr.getSize());
    std::cout << std::endl;

    // ---------- TRAVERSE (manual, using getData + getSize) ----------
    std::cout << "=== Manual traversal ===" << std::endl;
    const int *data = arr.getData();
    for (int i = 0; i < arr.getSize(); i++)
    {
        std::cout << "arr[" << i << "] = " << data[i] << std::endl;
    }
    std::cout << std::endl;

    // ---------- FILL TO CAPACITY, TEST isFull ----------
    std::cout << "=== Filling to capacity ===" << std::endl;
    arr.fill(100);
    utils.printArray(arr.getData(), arr.getSize());
    std::cout << "isFull: " << arr.isFull() << std::endl;

    // one more push should print "Array is full" and be rejected
    arr.push(1000);

    return 0;
}