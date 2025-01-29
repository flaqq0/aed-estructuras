#include <iostream>
using namespace std;

//lifo abc -> cba
template <typename T>
class Stack{
    struct Node{
        T data;
        Node* next;
        Node() : data(0), next(nullptr) {}
        explicit Node(T d) : data(d), next(nullptr) {}
        Node(T dato, Node* sig) : data(dato), next(sig) {}
    };
    Node* cima;
public:
    Stack() : cima(nullptr) {}

    bool isEmpty(){return cima == nullptr;}
    ~Stack(){
        while (!isEmpty()){
            pop();
        }
    }
    /*
    bool isFull(){
        if(cima >= MAX_STACK_SIZE-1) return true;
        return false;
    }
    */
    T top() {
        if(isEmpty()) return T();
        return cima->data;
    }
    void push(T val){
        Node* nuevo = new Node(val, cima);
        cima = nuevo;
    }
    void pop(){
        if(isEmpty()) return;
        Node* temp = cima;
        cima=cima->next;
        delete temp;
    }
    void print() {
        if (isEmpty())return;

        Node* temp = cima;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main(){
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