#include <iostream>

template <typename T>
class CircularDLLS {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node() : data(0), prev(nullptr), next(nullptr) {}
        explicit Node(T d) : data(d), prev(nullptr), next(nullptr) {}
        Node(T d, Node* p, Node* n) : data(d), prev(p), next(n) {}
    };

    Node* sentinel;
    int list_size;

public:
    CircularDLLS() {
        sentinel = new Node();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        list_size = 0;
    }

    ~CircularDLLS() {
        clear();
        delete sentinel;
    }

    T front() {
        return empty() ? T() : sentinel->next->data;
    }

    T back() {
        return empty() ? T() : sentinel->prev->data;
    }

    void push_front(T value) {
        Node* new_node = new Node{value, sentinel, sentinel->next};
        sentinel->next->prev = new_node;
        sentinel->next = new_node;
        list_size++;
    }

    void push_back(T value) {
        Node* new_node = new Node{value, sentinel->prev, sentinel};
        sentinel->prev->next = new_node;
        sentinel->prev = new_node;
        list_size++;
    }

    T pop_front() {
        if (empty()) return T();
        Node* first = sentinel->next;
        T value = first->data;
        sentinel->next = first->next;
        first->next->prev = sentinel;
        delete first;
        list_size--;
        return value;
    }

    T pop_back() {
        if (empty()) return T();
        Node* last = sentinel->prev;
        T value = last->data;
        sentinel->prev = last->prev;
        last->prev->next = sentinel;
        delete last;
        list_size--;
        return value;
    }

    void insert(T value, int position) {
        if (position < 0 || position > list_size) return;
        Node* current = sentinel;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        Node* new_node = new Node(value, current, current->next);
        current->next->prev = new_node;
        current->next = new_node;
        list_size++;
    }

    void remove(int position) {
        if (position < 0 || position >= list_size) return;
        Node* current = sentinel->next;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        list_size--;
    }

    int size() const {
        return list_size;
    }

    bool empty() const {
        return list_size == 0;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void reverse() {
        if (empty()) return;
        Node* current = sentinel;

        Node* temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
        while (current != sentinel) {
            temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        }
    }

    T operator[](int index) const {
        if (index < 0 || index >= list_size) return T();
        Node* current = sentinel->next;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void print() const {
        if (empty()) {
            std::cout << "Lista vacia" << std::endl;
            return;
        }

        Node* current = sentinel->next;
        while (current != sentinel) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    CircularDLLS<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.insert(4, 4);
    list.insert(5, 2);
    list.print(); // 0 1 5 2 3 4

    std::cout << "Front: " << list.front() << std::endl;
    std::cout << "Back: " << list.back() << std::endl;

    list.pop_front();
    list.pop_back();
    list.remove(2);
    list.print(); // 1 5 3

    list.reverse();
    list.print(); // 3 5 1
    std::cout << "Elemento en pos 1: " << list[1] << std::endl;

    list.clear();
    list.print(); // Lista vacía
    std::cout<<"La lista esta vacia? ";
    if (list.empty()) std::cout<<"Si"<<std::endl;
    else std::cout<<"No"<<std::endl;
    return 0;
}