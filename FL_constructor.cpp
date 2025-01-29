#include <iostream>
using namespace std;

template <typename T>
class forwardList{
private:
        struct Node{
            T data;
            Node* next;
            Node() : data(0), next(nullptr) {}
            explicit Node(T d) : data(d), next(nullptr) {}
            Node(T dato, Node* sig) : data(dato), next(sig) {}
        };

        Node* head = nullptr;
public:
    forwardList() : head(nullptr) {}
    ~forwardList() {clear(); }

    T front(){
        if(!head){
            return NULL;
        }
        return head->data;
    }
    T back(){
        if(!head) return NULL;
        Node* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        return curr->data;
    }
    void push_front(T inicio){
        //Agrega elemento al comienzo
        if(!head){
            head = new Node(inicio);
            return;
        }

        Node* first = new Node(inicio);

        Node* temp = head;
        head = first;
        head->next = temp;
    }
    void push_back(T final){
        //Agrega elemento al final
        if(!head){
            head = new Node(final);
            return;
        }
        Node* curr = head;
        while (curr->next){
            curr = curr->next;
        }
        curr->next = new Node(final);
    }
    T pop_front(){
        //elimina el elemento al comienzo
        if(!head) return NULL;
        T data = head->data;
        if(!head->next){
            delete head;
            head= nullptr;
            return data;
        }
        Node* first = head->next;
        delete head;
        head= nullptr;
        head = first;
        return data;
    }
    T pop_back(){
        //elimina el elemento al final
        if(!head) return NULL;
        if(!head->next){
            T data = head->data;
            delete head;
            head= nullptr;
            return data;
        }
        Node* curr = head;
        while (curr->next && curr->next->next) {
            curr = curr->next;
        }
        T data = curr->next->data;
        delete curr->next;
        curr->next = nullptr;
        return data;
    }

    bool empty(){//está vacio?
        return head == nullptr;// cabeza es igual a nulo? Sí, entonces TRUE. no, entonces FALSE
    }
    int size(){
        int c = 0;
        Node* curr = head;
        while (curr) {
            c++;
            curr = curr->next;
        }
        return c;
    }// Retorna el tamaño de la lista

    T operator[](int index) {
        // Retorna el elemento en la posición indicada
        if (index >= 0 && index < size()) {
            Node *temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->data;
        }
        return NULL;
    }

    void clear(){
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    } // Elimina todos los elementos de la lista

    void split(Node* source, Node** front, Node** back) {
        if (!source || !source->next) {
            *front = source;
            *back = nullptr;
            return;
        }

        Node* slow = source;
        Node* fast = source->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        Node* result = nullptr;

        if (left->data <= right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }

        return result;
    }

    void mergeSort(Node** headRef) {
        if (!(*headRef) || !((*headRef)->next)) return;

        Node* left;
        Node* right;

        split(*headRef, &left, &right);

        mergeSort(&left);
        mergeSort(&right);

        *headRef = merge(left, right);
    }

    void sort() {
        mergeSort(&head);
    } // Implemente un algoritmo de ordenacion con listas enlazadas

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr) {
            next = curr->next;  //siguiente nodo
            curr->next = prev;  // Invert puntero
            prev = curr;
            curr = next;
        }

        head = prev;  // Actualizar la cabeza de la lista
    } // Revierte la lista
};

int main(){
    forwardList<int> lista;
    lista.push_front(1);
    lista.push_back(2);
    lista.push_back(3);
    lista.push_back(4);
    lista.push_back(5);


    cout<<"Lista original: ";
    for (int i = 0; i < lista.size(); i++) cout << lista[i] << " ";
    cout << endl;
    cout<<endl;

    cout<<"Elemento al comienzo: "<<lista.front()<<endl;
    cout<<"Elemento al final: "<<lista.back()<<endl;
    cout<<endl;

    lista.push_front(9);
    cout<<"Agregar 9 al comienzo: ";
    for (int i = 0; i < lista.size(); i++) cout << lista[i] << " ";
    cout<<endl;

    lista.push_back(10);
    cout<<"Agregar 10 al final: ";
    for (int i = 0; i < lista.size(); i++) cout << lista[i] << " ";
    cout<<endl;
    cout<<endl;

    cout<<"Remover el elemento al comienzo: "<<lista.pop_front()<<endl;
    for (int i = 0; i < lista.size(); i++) cout << lista[i] << " ";
    cout<<endl;

    cout<<"Remover el elemento del final: "<<lista.pop_back()<<endl;
    for (int i = 0; i < lista.size(); i++) cout << lista[i] << " ";
    cout<<endl;
    cout<<endl;

    cout<<"La lista esta vacia?"<<endl;
    if(lista.empty())cout<<"Si"<<endl;
    else{
        cout<<"No, su tamano es de "<<lista.size()<<endl;
    }
    cout<<endl;

    lista.reverse();
    cout << "Lista invertida: ";
    for (int i = 0; i < lista.size(); i++) cout << lista[i] << " ";
    cout << endl;
    cout<<endl;

    cout<<"Ordenar la lista de menor a mayor: ";
    lista.sort();
    for (int i = 0; i < lista.size(); i++) cout << lista[i] << " ";
    cout<<endl;

    cout<<"limpio la lista."<<endl;
    lista.clear();
    cout<<"La lista esta vacia?"<<endl;
    if(lista.empty())cout<<"Si"<<endl;
    else{
        cout<<"No, su tamano es de "<<lista.size()<<endl;
    }
    cout<<endl;

    return 0;
}