#include <iostream>
using namespace std;


template <typename T>
struct Node {
    T data;
    Node* next;
};


template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* merge(Node<T>* first, Node<T>* second) {
        if (!first)return second;
        if (!second)return first;
        if (first->data < second->data) {
            first->next = merge(first->next,second);
            return first;
        } else {
            second->next = merge(first,second->next);
            return second;
        }
    }
    Node<T>* mergeSort(Node<T>* head) {
        if (!head || !head->next)return head;
        Node<T>* slow = head;
        Node<T>* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node<T>* temp = slow->next;
        slow->next = nullptr;
        return merge(mergeSort(head), mergeSort(temp));
    }


public:
    List(){head = nullptr;}
    ~List() {clear();}
    T front(){
        if(head != nullptr)return head->data;
        return T();
    }
    T back(){
        if(head != nullptr){
            Node<T>* temp = head;
            while(temp->next != nullptr){temp = temp->next;}
            return temp->data;
        }
        return T();
    }
    void push_front(T data){
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }
    void push_back(T data){
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;
        if(!head)head = newNode;
        else{
            Node<T>* temp = head;
            while(temp->next != nullptr){temp = temp->next;}
            temp->next = newNode;
        }
    }
    T pop_front(){
        if (head) {
            Node<T>* temp = head;
            T data = temp->data;
            head = head->next;
            delete temp;
            return data;
        }
        return T();
    }
    T pop_back(){
        if(head){
            Node<T>* temp = head;
            Node<T>* prev = nullptr;
            while(temp->next != nullptr){
                prev = temp;
                temp = temp->next;
            }
            if(prev)prev->next = nullptr;
            else head = nullptr;
            T data = temp->data;
            delete temp;
            return data;
        }return T();
    }
    T operator[](int index) {
        if (index > 0 && index <= size()) {
            Node<T> *temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->data;
        }
        return NULL;
    }

    bool isEmpty(){
        return head == nullptr;
    }
    void insert(int index, T data){
        if (index < 0 || index > size()) return;
        if (index == 0) {
            push_front(data);
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = temp->next;
        temp->next = newNode;
    }
    void remove(int index){
        if (index < 0 || index >= size() || !head) return;
        if (index == 0) {
            pop_front();
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        Node<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
    int size(){
        int count = 0;
        Node<T>* temp = head;
        while(temp != nullptr){
            temp = temp->next;
            count++;
        }return count;
    }
    void clear(){
        while(head != nullptr){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void sort() {
        head = mergeSort(head);
    }
    void reverse(){
        if(head != nullptr){
            Node<T>* prev = nullptr;
            Node<T>* current = head;
            Node<T>* next = nullptr;
            while(current != nullptr){
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }head = prev;
        }
    }
    Node<T> *getHead(){
        return head;
    }
    friend ostream& operator<<(ostream& os, List<T>& list){
        Node<T>* temp = list.head;
        os << "[";
        while(temp != nullptr){
            os << temp->data;
            if (temp->next != nullptr){
                os << ", ";
            }
            temp = temp->next;
        }
        os << "]";
        return os;
    }
};
int main() {
    //enteros
    List<int> list;
    list.push_back(110);
    list.push_back(34);
    list.push_front(93);
    cout << "Lista inicial: " << list << endl; // 93 110 34

    // Insertar en pos
    list.insert(1, 15);  // 15 en la pos 1
    cout << "insert(1, 15): " << list << endl; // 93 15 110 34

    // Eliminar
    list.remove(2); // Elimina en pos 2
    cout << "remove(2): " << list << endl; //93 15 34

    // Revertir
    list.reverse();
    cout << "reverse(): " << list << endl; //34 15 93

    // Ordenar
    list.sort();
    cout << "sort(): " << list << endl; //93 15 34

    // []
    cout << "Eliminar posicion 1: " << list[1] << endl; // 15

    // Limpiar
    list.clear();
    cout << "clear(): " << list << endl; // []

    cout << "\n-----------------------------\n";

    List<string> stringList;
    stringList.push_back("uno");
    stringList.push_back("dos");
    stringList.push_front("cero");
    cout << "Lista inicial: " << stringList << endl; // cero, uno, dos

    // Insertar en una posición válida
    stringList.insert(2, "uno y medio");
    cout << "insert(2, 'uno y medio'): " << stringList << endl; // cero  uno  uno y medio  dos

    // pop_front y pop_back
    cout << "pop_front(): " << stringList.pop_front() << endl; // cero
    cout << "pop_back(): " << stringList.pop_back() << endl;   // dos
    cout << "Despues de pops: " << stringList << endl; // uno   uno y medio

    cout << "\n-----------------------------\n";

    List<double> emptyList;
    cout << "Lista vacia?: " << (emptyList.isEmpty() ? "Si" : "No") << endl; // Sí
    emptyList.push_front(1.1);
    cout << "Lista vacia luego de push_front?: " << (emptyList.isEmpty() ? "Si" : "No") << endl; // No
    emptyList.clear();
    cout << "Lista vacia luego de clear?: " << (emptyList.isEmpty() ? "Si" : "No") << endl; // Sí

    cout << "\n-----------------------------\n";

    List<int> sortList;
    sortList.push_back(67);
    sortList.push_back(5);
    sortList.push_back(99);
    sortList.push_back(21);
    cout << "antes de sort(): " << sortList << endl; // 67, 5, 99, 21
    sortList.sort();
    cout << "luego de sort(): " << sortList << endl; // 5, 21, 67, 99

    return 0;
}
