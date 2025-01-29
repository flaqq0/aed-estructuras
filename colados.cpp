#include <iostream>
using namespace std;

#define MAX_QUEUE_SIZE 100

template <typename T>
class StaticQueue {
private:
    T list[MAX_QUEUE_SIZE];
    int frontIdx, rearIdx;

public:
    StaticQueue() {
        frontIdx = 0;
        rearIdx = 0;
    }

    bool isFull() {
        return frontIdx == (rearIdx + 1) % MAX_QUEUE_SIZE;
    }

    bool isEmpty() {
        return frontIdx == rearIdx;
    }

    T front() {
        if (isEmpty()) return T();
        return list[(frontIdx + 1) % MAX_QUEUE_SIZE];
    }

    void enqueue(T val) {
        if (isFull()) return;
        rearIdx = (rearIdx + 1) % MAX_QUEUE_SIZE;
        list[rearIdx] = val;
    }

    void dequeue() {
        if (isEmpty())return;
        frontIdx = (frontIdx + 1) % MAX_QUEUE_SIZE;
    }

    void print() {
        if (isEmpty()) return;
        cout << "Cola: ";
        for (int i = (frontIdx + 1) % MAX_QUEUE_SIZE; i != (rearIdx + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE) {
            cout << list[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    StaticQueue<int> queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.print(); // 10 20 30

    cout << "Front: " << queue.front() << endl; // 10

    queue.dequeue();
    queue.print(); // 20 30

    queue.enqueue(40);
    queue.enqueue(50);
    queue.print(); // 20 30 40 50

    return 0;
}
