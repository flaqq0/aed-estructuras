#include <iostream>
using namespace std;

template <typename T>
class DQueue {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(T val) : data(val), next(nullptr) {}
    };

    Node* frontPtr;
    Node* rearPtr;
    int size;

public:
    DQueue() {
        frontPtr = rearPtr = nullptr;
        size = 0;
    }

    ~DQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return size == 0;
    }

    T front() {
        if (isEmpty()) return T();
        return frontPtr->data;
    }

    void enqueue(T val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        size++;
    }

    void dequeue() {
        if (isEmpty()) return;
        Node* temp = frontPtr;
        frontPtr = frontPtr->next;
        delete temp;
        size--;
        if (isEmpty()) rearPtr = nullptr;
    }

    void print() {
        if (isEmpty()) return;
        cout << "Cola: ";
        Node* current = frontPtr;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main(){
    DQueue<string> cola;
    cola.enqueue("Hola");
    cola.enqueue("Mundo");
    cola.enqueue("C++");
    cola.print(); // Hola Mundo C++
    cout << "Front: " << cola.front() << endl;
    cola.dequeue();
    cola.print(); // Mundo C++

    return 0;
}