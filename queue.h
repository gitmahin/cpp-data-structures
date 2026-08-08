// Copyright (c) 2026 Nimul Islam Mahin and contributors
// SPDX-License-Identifier: MIT
// See the LICENSE file for details.

#include <iostream>

// =========================================================
// Linear Queue
// =========================================================
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
template <typename T>
class LinearQueue
{
public:
    LinearQueue(int size) : rear(-1), size(size), data(new T[size]) {}

    ~LinearQueue()
    {
        delete[] this->data;
    }

private:
    int size;
    T *data = nullptr;
    int rear;

public:
    void enqueue(const T &data);
    const T dequeue();
    const T &frontElement() const;
    const T &rearElement() const;
    const T &peek(int position) const;
    void traverse();
    const bool isEmpty() const;
    const bool isFull() const;
};

// =========================================================
// Circular Queue
// =========================================================
/**
 * This implementation improves upon the Linear Queue by using a "wraparound"
 * strategy. This eliminates the need for O(n) element shifting during dequeue.
 *
 * NOTE: One slot in the array is intentionally left empty to distinguish
 * between the 'Full' and 'Empty' states.
 *
 * Time Complexities:
 * - enqueue()       : O(1) - Constant time insertion at the rear.
 * - dequeue()       : O(1) - Constant time removal (pointer update only).
 * - frontElement()  : O(1) - Direct access using front pointer.
 * - rearElement()   : O(1) - Direct access using rear pointer.
 * - peek()          : O(1) - Calculated access using modulo.
 * - traverse()      : O(n) - Linear time to visit every valid element.
 * - isEmpty/isFull(): O(1) - Simple conditional pointer checks.
 *
 * Alternative Strategies
 * 1. https://medium.com/@e_moreira/circular-queue-a-generic-data-structure-for-efficient-memory-management-c61d8fa88076 [Thanks to the writer]
 */
template <typename T>
class CircularQueue
{
public:
    CircularQueue(int size) : front(0), rear(0), size(size + 1), data(new T[size]) {}

    ~CircularQueue()
    {
        delete[] this->data;
    }

private:
    int size;
    T *data = nullptr;
    int rear;
    int front;
    const int countValidElement() const;

public:
    void enqueue(const T &data);
    const T &dequeue();
    const T &frontElement() const;
    const T &rearElement() const;
    const T &peek(int position) const;
    void traverse();
    const bool isEmpty() const;
    const bool isFull() const;
};

// ===== Linear Queue Implementations ===================================
template <typename T>
const bool LinearQueue<T>::isEmpty() const
{
    if (this->rear == -1)
    {
        return true;
    }
    return false;
}

template <typename T>
const bool LinearQueue<T>::isFull() const
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
const T LinearQueue<T>::dequeue()
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
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
const T &LinearQueue<T>::frontElement() const
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
    }
    return this->data[0];
}

template <typename T>
const T &LinearQueue<T>::rearElement() const
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
    }

    return this->data[this->rear];
}

template <typename T>
const T &LinearQueue<T>::peek(int position) const
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
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

// ===== Circular queue implementations ===================================
// ┌─────────────────────────────────┐
// │ Theory of valid element count   │
// └─────────────────────────────────┘
/**
 * This calculates how many elements are currently in the queue.
 *
 * Important thing to know first:
 * `front` does NOT point to a real element. It points to the slot of the
 * item that was MOST RECENTLY removed (or, if nothing has been removed
 * yet, it points to a starting "empty" slot before the first element).
 * The actual first valid element is always at (front + 1).
 *
 * Picture the array not as a straight line, but as a circle of slots,
 * like a clock face. `enqueue` always moves `rear` one step CLOCKWISE
 * (0 → 1 → 2 → ... → last index → back to 0 → 1 → ...). It never moves
 * counter-clockwise. So to count elements, we're really measuring the
 * clockwise distance from (front + 1) to rear.
 *
 * --------------------------------------------------------------
 * CASE 1: rear > front  (rear hasn't looped past index 0 yet)
 * --------------------------------------------------------------
 * Example: front = 1, rear = 5
 * Walking clockwise from front, the valid elements sit at indices: 2, 3, 4, 5
 * That's 4 elements, and notice: rear - front = 5 - 1 = 4.
 *
 * So when rear is bigger than front, we can just do:
 *      count = rear - front
 *
 * --------------------------------------------------------------
 * CASE 2: rear <= front  (rear has looped clockwise past index 0
 *                         and is now numerically behind front)
 * --------------------------------------------------------------
 * This happens because the queue is circular. `rear` keeps moving
 * CLOCKWISE, and once it passes the last index, the next clockwise step
 * lands back on index 0. So `rear` can end up with a smaller number
 * than `front`, even though rear is still "ahead" of front if you trace
 * the clockwise path instead of comparing raw numbers.
 *
 * Example: front = 6, rear = 2, size = 11 (indices go from 0 to 10)
 * Walking clockwise from front (6 → 7 → 8 → 9 → 10 → 0 → 1 → 2), the
 * valid elements are at indices: 7, 8, 9, 10, 0, 1, 2
 * That's 7 elements.
 *
 * How do we calculate that with math instead of counting by hand?
 * Think of it in two parts:
 *   - Walking COUNTER-CLOCKWISE from front back to rear covers the
 *     EMPTY part of the queue: front - rear = 6 - 2 = 4
 *   - The queue's total size is 11.
 *   - So the FILLED part (what we actually want) is everything else:
 *     11 - 4 = 7
 *
 * So when rear is smaller than (or equal to) front, we do:
 *      count = size - (front - rear)
 *
 * ---------------------------------------------------------
 * Key takeaway:
 * ---------------------------------------------------------
 * `rear` only ever moves CLOCKWISE, one step at a time, looping from
 * the last index back to 0 when needed. It never moves counter-clockwise.
 * That's why "front chasing rear" is always a clockwise journey — and
 * why a small `rear` number doesn't always mean "behind" front.
 */

// ┌────────────────────────────────────────────────────────────┐
// │ Visualization for circular queue and valid element count   │
// └────────────────────────────────────────────────────────────┘
/**
 * Visual: size = 11 (indices 0-10), front = 6, rear = 2
 *
 *                    0 (valid)
 *            10               1 (valid)
 *         (valid)
 *                                  2 <- rear (valid)
 *      9 (valid)
 *                                  3 (empty)
 *      8 (valid)
 *                                  4 (empty)
 *         7 (valid)
 *            6 <- front         5 (empty)
 *                   (empty)
 *
 *   Clockwise order starting right after front:
 *   front(6) -> 7 -> 8 -> 9 -> 10 -> 0 -> 1 -> 2(rear)
 *               ^-------- valid elements (7 of them) --------^
 *
 *   Then continuing clockwise back to front:
 *   2(rear) -> 3 -> 4 -> 5 -> 6(front)
 *              ^---- empty slots (4 of them) ----^
 *
 *   valid (7) + empty (4) = size (11)
 *
 *
 * # Circular shape Designed by Claude - Sonnet 5 (Medium)
 */
template <typename T>
const int CircularQueue<T>::countValidElement() const
{

    if (this->rear > this->front)
    {
        return (this->rear - this->front);
    }
    else
    {
        return (this->size - (this->front - this->rear));
    }
}

// Check if queue is empty or not
template <typename T>
const bool CircularQueue<T>::isEmpty() const
{
    if (this->rear == this->front)
    {
        return true;
    }
    return false;
}

// Check if queue is full or not
template <typename T>
const bool CircularQueue<T>::isFull() const
{
    if (((this->rear + 1) % this->size) == this->front)
    {
        return true;
    }
    return false;
}

// Inserts a new element at the end (rear) of the queue.
template <typename T>
void CircularQueue<T>::enqueue(const T &data)
{
    if (this->isFull())
    {
        std::cout << "Queue is full!" << " " << data << std::endl;
        return;
    }

    this->rear = (this->rear + 1) % this->size;
    this->data[this->rear] = data;
    std::cout << "Enqueued: " << data << std::endl;
}

template <typename T>
const T &CircularQueue<T>::dequeue()
{
    // Ensure the queue is not empty before removal
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
    }

    /**
     * Moves the front pointer forward using the modulo operator to achieve a "wraparound" effect.
     * This effectively turns a linear array into a circular buffer.
     *
     * Example:
     * Suppose Queue Size = 5 (Indices: 0, 1, 2, 3, 4)
     * Current front = 4 (The pointer is at the very last element)
     *
     * Without Modulo: front + 1 = 5 (Index 5 is out of bounds!)
     * With Modulo:    (4 + 1) % 5 = 0
     *
     * Result: The pointer "wraps around" from index 4 back to index 0, allowing
     * the queue to reuse the freed space at the start of the array.
     *
     * Note: Same for this->rear also
     */
    this->front = (this->front + 1) % this->size;
    return this->data[this->front];
}

// Get front element from the queue
template <typename T>
const T &CircularQueue<T>::frontElement() const
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
    }
    return this->data[(this->front + 1) % this->size];
}

// Get last element from the queue
template <typename T>
const T &CircularQueue<T>::rearElement() const
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
    }

    return this->data[this->rear % this->size];
}

/**
 * Returns the element at a specific logical position (1st, 2nd, etc.)
 *
 * Logic:
 * 1. (this->front + 1) -> Locates the first actual element (since front is a sentinel).
 * 2. (position - 1)    -> Converts 1-based human position to 0-based offset.
 * 3. % this->size      -> Wraps the index around to the start of the array if it exceeds the bounds.
 *
 * Simplified: (front + position) % size
 */
template <typename T>
const T &CircularQueue<T>::peek(int position) const
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        static const T empty{};
        return empty;
    }

    /**
     * Boundary Check: Validates that the requested logical position exists
     * within the current range of enqueued elements.
     *
     * 1. position <= 0: Handles invalid non-positive indexing (since peek is 1-based).
     * 2. count < position: Prevents "reading ahead" into empty slots or stale data
     *    beyond the current number of elements in the queue.
     */
    if (this->countValidElement() < position || position <= 0)
    {
        std::cout << "Out of Bounds: Position " << position << " does not exist!" << std::endl;
        static const T empty{};
        return empty;
    }

    return this->data[(this->front + (position - 1) + 1) % this->size];
}

template <typename T>
void CircularQueue<T>::traverse()
{
    if (this->isEmpty())
    {
        std::cout << "Queue is Empty!" << std::endl;
        return;
    }

    int count = this->countValidElement(); // counter for traversing queue

    /**
     * Start one slot AFTER front, because front itself holds stale
     * (already-dequeued) data, not a current element.
     */
    int circular_index = (this->front + 1) % this->size;
    ;
    for (int i = 0; i < count; i++)
    {
        std::cout << "[" << i + 1 << "]: " << this->data[circular_index] << std::endl;

        /**
         * Advance and wrap around using modulo so we treat the
         * array as circular instead of running off the end.
         */
        circular_index = (circular_index + 1) % this->size;
    }
}
