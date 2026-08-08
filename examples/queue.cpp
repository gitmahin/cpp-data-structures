#include <iostream>
#include "../queue.h"  // adjust path to match your project structure

void demoLinearQueue()
{
    LinearQueue<int> queue(5);

    // ---------- CREATE ----------
    std::cout << "=== Created LinearQueue (size 5) ===" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "isEmpty: " << queue.isEmpty() << std::endl;
    std::cout << std::endl;

    // ---------- ENQUEUE ----------
    std::cout << "=== Enqueuing 10, 20, 30, 40 ===" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    queue.traverse();
    std::cout << std::endl;

    // ---------- FRONT / REAR / PEEK ----------
    std::cout << "=== Element access ===" << std::endl;
    std::cout << "frontElement: " << queue.frontElement() << std::endl;
    std::cout << "rearElement: " << queue.rearElement() << std::endl;
    std::cout << "peek(2): " << queue.peek(2) << std::endl; // 1-indexed -> data[1] = 20
    std::cout << std::endl;

    // ---------- DEQUEUE ----------
    std::cout << "=== dequeue() ===" << std::endl;
    int dequeued = queue.dequeue();
    std::cout << "dequeued value: " << dequeued << std::endl;
    queue.traverse();
    std::cout << std::endl;

    // ---------- FILL TO CAPACITY ----------
    std::cout << "=== Filling to capacity ===" << std::endl;
    queue.enqueue(50);
    queue.enqueue(60); // queue now full (size 5)
    queue.traverse();
    std::cout << "isFull: " << queue.isFull() << std::endl;

    // one more enqueue should print "Queue is full!" and be rejected
    queue.enqueue(999);
    std::cout << std::endl;

    // ---------- DRAIN THE QUEUE ----------
    std::cout << "=== Draining queue ===" << std::endl;
    while (!queue.isEmpty())
    {
        std::cout << "dequeued: " << queue.dequeue() << std::endl;
    }

    // dequeue on empty queue should print "Queue is Empty!"
    queue.dequeue();
}

void demoCircularQueue()
{
    // Internally allocates size+1 slots (4+1=5), one slot always kept
    // empty to distinguish "full" from "empty" when front == rear.
    CircularQueue<int> queue(4);

    // ---------- CREATE ----------
    std::cout << "=== Created CircularQueue (usable capacity 4) ===" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "isEmpty: " << queue.isEmpty() << std::endl;
    std::cout << std::endl;

    // ---------- ENQUEUE ----------
    std::cout << "=== Enqueuing 10, 20, 30, 40 ===" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    queue.traverse();
    std::cout << std::endl;

    // ---------- FRONT / REAR / PEEK ----------
    std::cout << "=== Element access ===" << std::endl;
    std::cout << "frontElement: " << queue.frontElement() << std::endl;
    std::cout << "rearElement: " << queue.rearElement() << std::endl;
    std::cout << "peek(2): " << queue.peek(2) << std::endl; // logical 2nd element -> 20
    std::cout << std::endl;

    // ---------- FULL CHECK (queue is already full: 4 elements, 1 slot reserved) ----------
    std::cout << "=== isFull check ===" << std::endl;
    std::cout << "isFull: " << queue.isFull() << std::endl;
    // this should print "Queue is full!" and reject
    queue.enqueue(999);
    std::cout << std::endl;

    // ---------- DEQUEUE (this is where wraparound becomes visible) ----------
    std::cout << "=== dequeue() x2 ===" << std::endl;
    std::cout << "dequeued: " << queue.dequeue() << std::endl; // removes 10
    std::cout << "dequeued: " << queue.dequeue() << std::endl; // removes 20
    queue.traverse();
    std::cout << std::endl;

    // ---------- ENQUEUE AGAIN: rear wraps around past the end of the array ----------
    std::cout << "=== Enqueuing 50, 60 (rear wraps around) ===" << std::endl;
    queue.enqueue(50);
    queue.enqueue(60);
    queue.traverse();
    std::cout << std::endl;

    // ---------- PEEK OUT OF BOUNDS ----------
    std::cout << "=== peek(10) - invalid position ===" << std::endl;
    queue.peek(10); // should print "Out of Bounds"
    std::cout << std::endl;

    // ---------- DRAIN THE QUEUE ----------
    std::cout << "=== Draining queue ===" << std::endl;
    while (!queue.isEmpty())
    {
        std::cout << "dequeued: " << queue.dequeue() << std::endl;
    }

    // dequeue on empty queue should print "Queue is Empty!"
    queue.dequeue();
}

int main()
{
    demoLinearQueue();

    std::cout << "\n========================================\n" << std::endl;

    demoCircularQueue();

    return 0;
}