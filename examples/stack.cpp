#include <iostream>
#include "../stack.h"
#include <string>

int main()
{
    /* ---------------------------------------------------------------- */
    /*                     Basic push / pop / peek                      */
    /* ---------------------------------------------------------------- */
    std::cout << "== Basic int stack ==" << std::endl;

    Stack<int> stack(5);

    std::cout << "isEmpty: " << stack.isEmpty() << std::endl; // 1 (true)

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top element: " << stack.htop() << std::endl; // 30
    stack.traverse();                                          // 30 20 10

    int popped = stack.pop();
    std::cout << "Popped: " << popped << std::endl; // 30
    stack.traverse();                                // 20 10

    std::cout << "Size (capacity): " << stack.getSize() << std::endl; // 5
    std::cout << "isEmpty: " << stack.isEmpty() << std::endl;         // 0 (false)

    /* ---------------------------------------------------------------- */
    /*                     Overflow / underflow checks                   */
    /* ---------------------------------------------------------------- */
    std::cout << "\n== Overflow / underflow ==" << std::endl;

    Stack<int> tiny(2);

    tiny.push(1);
    tiny.push(2);
    tiny.push(3); // "Stack Overflow!" - push ignored

    std::cout << "isFull: " << tiny.isFull() << std::endl; // 1 (true)

    tiny.pop();
    tiny.pop();
    int result = tiny.pop(); // "Stack Underflow!" — returns default int (0)

    std::cout << "result after underflow: " << result << std::endl; // 0

    /* ---------------------------------------------------------------- */
    /*                     Stack of std::string                          */
    /* ---------------------------------------------------------------- */
    std::cout << "\n== std::string stack ==" << std::endl;

    Stack<std::string> history(3);

    history.push("open");
    history.push("edit");
    history.push("save");

    std::cout << "Top: " << history.htop() << std::endl; // "save"
    history.traverse();                                  // save edit open

    history.pop();
    std::cout << "Top after pop: " << history.htop() << std::endl; // "edit"

    return 0;
}