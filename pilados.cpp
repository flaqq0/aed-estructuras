#include <iostream>
using namespace std;
#define MAX_STACK_SIZE 100

struct element {
    int key;
};

template <typename T>
class Stack {
private:
    T list[MAX_STACK_SIZE];
    int cima;

public:
    Stack() {cima = -1;}

    bool isEmpty() {
        return cima == -1;
    }

    int isFull() {
        if(cima >= MAX_STACK_SIZE - 1) return true;
        return false;
    }

    void push(T val) {
        if (isFull()) {return;}
        list[++cima] = val;
    }

    void pop() {
        if (isEmpty()) return;
        cima--;
    }

    T top() {
        if (isEmpty()) {
            return T();
        }
        return list[cima];
    }

    void print() {
        if (isEmpty()) {
            return;
        }
        for (int i = cima; i >= 0; i--) {
            cout << list[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack<int> pila;
    pila.push(1);
    pila.push(2);
    pila.push(3);
    pila.print(); // 3 2 1

    cout << "Tope: " << pila.top() << endl; // 3

    pila.pop();
    pila.print(); // 2 1

    return 0;
}