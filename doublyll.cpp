#include <iostream>
using namespace std;
template <typename T>
class doublyll{
private:
    struct Node{
        T data;
        Node* next;
        Node* prev;
        Node() : data(0), next(nullptr), prev(nullptr) {}
        explicit Node(T d) : data(d), next(nullptr), prev(nullptr) {}
        Node(T dato, Node* sig, Node* pv) : data(dato), next(sig), prev(pv) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
public:
    doublyll() : head(nullptr), tail(nullptr) {}
    ~doublyll(){clear();}

    T front(){
        if(head){
            return head->data;
        } else return T();
        //retorna elemento al comienzo
    }

    T back(){
        // Retorna el elemento al final
        if (tail) return tail->data;
        else return T();
    }
    void push_front(T val){
        // Agrega un elemento al comienzo
        Node* nuevo = new Node(val);
        if(head){
            nuevo->next=head;
            head->prev = nuevo;
        }
        head = nuevo;
        if(!tail){
            tail = head;
        }
    }
    void push_back(T val){
        // Agrega un elemento al final
        Node* nuevo = new Node(val);
        if(!head) head = nuevo;
        if(tail){
            tail->next = nuevo;
            nuevo->prev = tail;
        }
        tail = nuevo;
    }
    T pop_front(){
        // Remueve el elemento al comienzo
        if(!head) return T();

        T data = head->data;
        Node* temp = head;

        head = head->next;
        if(head) head->prev= nullptr;
        else tail= nullptr;
        delete temp;
        return data;
    }
    T pop_back(){
        // Remueve el elemento al final
        if(!tail) return T();

        T data = tail->data;
        Node* temp = tail;

        tail = tail->prev;
        if(tail) tail->next = nullptr;
        else head= nullptr;

        delete temp;
        return data;
    }
    void insert(T val, int pos){
        // Inserta en cualquier posición
        if(pos<0) return;
        if (pos==0){
            push_front(val);
            return;
        }
        Node* curr =head;
        for(int i=0; i<pos-1; i++){
            if(!curr) return;
            curr=curr->next;
        }
        if(!curr || !curr->next){
            /*
            Node* nuevo = new Node(val, curr, nullptr);
            if (curr) curr->next = nuevo;
            tail=nuevo;
            */
            push_back(val);
            return;
        }
        Node* nuevo = new Node(val, curr->next, curr);
        if(curr->next) curr->next->prev = nuevo;
        curr->next=nuevo;
    }
    void remove(int pos){
        // Remueve en cualquier posicion
        if(pos<0 or !head) return;
        if(pos==0){
            pop_front();
            return;
        }

        Node* curr= head;
        for(int i=0; i<pos; i++){
            if(!curr->next) return;
            curr=curr->next;
        }
        if(curr==tail){
            pop_back();
            return;
        }
        curr->prev->next= curr->next;
        curr->next->prev= curr->prev;
        delete curr;
    }
    T operator[ ](int index){
        // Retorna el elemento en la posición indicada
        if(index<0 || index>=size()) return T();

        Node *temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    bool empty(){
        // Retorna si la lista está vacía o no
        return head== nullptr;
    }
    int size(){
        // Retorna el tamaño de la lista
        int c=0;
        for (Node* curr = head; curr; curr = curr->next) c++;
        return c;
    }
    void clear(){
        // Elimina todos los elementos de la lista
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail= nullptr;
    }
    void reverse(){
        if(!head or !head->next) return;
        Node* curr = head;
        Node* temp = nullptr;

        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        swap(head, tail);
    }
    void print(){
        //imprimir
        for (Node* curr = head; curr; curr = curr->next) {
            cout << curr->data << " ";
        }
        cout << endl;
    }
};

int main(){
    doublyll<int> lista;

    lista.push_front(3);
    lista.push_front(2);
    lista.push_front(1);
    lista.push_back(4);
    lista.push_back(5);
    lista.push_back(6);

    cout << "Lista original: ";
    lista.print();

    cout << "Front: " << lista.front() << ", Back: " << lista.back() << endl;

    lista.insert(10, 2);
    cout << "Inserto 10 en pos 2: ";
    lista.print();

    lista.remove(4);
    cout << "Elimino el elemento en pos 4: ";
    lista.print();

    lista.reverse();
    cout << "Lista invertida: ";
    lista.print();

    cout << "Elemento en pos 2: " << lista[2] << endl;

    cout << "Tamano: " << lista.size() << endl;
    cout << "Lista vacia?: " << (lista.empty() ? "Si" : "No") << endl;

    lista.clear();
    cout << "Lista luego de limpiar: ";
    lista.print();
    cout << "Lista vacia?: " << (lista.empty() ? "Si" : "No") << endl;
}