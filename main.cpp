#include <iostream>
using namespace std;

template <typename T>
class CircularDLL{
    struct Node{
        T data;
        Node* next;
        Node* prev;
        Node() : data(0), next(nullptr), prev(nullptr) {}
        Node(T d) : data(d), next(nullptr), prev(nullptr) {}
        Node(T dato, Node* sig, Node* previo) : data(dato), next(sig), prev(previo) {}
    };

    T val;
    Node* head = nullptr;
    Node* cola = nullptr;
public:
    CircularDLL() : val(0), head(nullptr), cola(nullptr) {}
    CircularDLL(T v) : val(v), head(nullptr), cola(nullptr) {}
    CircularDLL(T v, Node* h, Node* t) : val(v), head(h), cola(t) {}

    T front() const {return head->data;}

    T back() const {return cola->data;}

    bool empty() const{return head == nullptr;}

    void crearCDLLfromList(const int arr[], T n){
        if (n <= 0) return;

        for (int i = 0; i < n; i++) {
            push_back(arr[i]);
        }
    }

    void push_back(T n){
        Node* ptr= new Node(n);
        if (empty()){
            push_front(n);
        }else{
            ptr->prev = cola;
            ptr->next = head;
            cola->next = ptr;
            head->prev = ptr;
            cola = ptr;
        }
    }
    void imprimir(){
        if (empty()) {
            cout << "Lista vacía" << endl;
            return;
        }
        Node* ptr = head;
        do {
            cout << ptr->data << " ";
            ptr = ptr->next;
        } while (ptr != head);
        cout << endl;
    }
    void push_front(T n){
        Node* ptr = new Node(n);
        if(empty()){
            ptr->prev = ptr;
            ptr->next = ptr;
            head=cola=ptr;
        }else {
            ptr->prev = cola;
            ptr->next = head;
            cola->next = ptr;
            head->prev = ptr;
            head = ptr;
        }
    }
    int size(){
        if(empty()) return 0;
        int t=0;
        Node* curr = head;
        do{
            t++;
            curr=curr->next;
        }while (curr!=head);
        return t;
    }

    void insert(T num, int pos){
        if (empty()){
            cout<<"Lista vacia"<<endl;
            return;
        }
        if (pos<0) {
            cout<<"Posicion invalida"<<endl;
            return;
        }
        if(size()<pos) {
            cout << "Posicion invalida" << endl;
            return;
        }
        if (pos==0){
            push_front(num);
            return;
        }
        if (pos==size()) {
            push_back(num);
            return;
        }
        Node* new_node = new Node(num);
        Node* curr = head;
        for (int i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        new_node->next = curr;
        new_node->prev = curr->prev;
        curr->prev->next = new_node;
        curr->prev = new_node;
    }
    void pop_front(){
        if(empty()){
            cout<<"Lista vacia"<<endl;
            return;
        }
        if (head==cola){
            delete head;
            head=cola= nullptr;
        } else{
            Node* temp = head;
            head = head->next;
            head->prev = cola;
            cola->next = head;
            delete temp;
        }
    }
    void pop_back(){
        if(empty()){
            cout<<"Lista vacia"<<endl;
            return;
        }
        if (head==cola){
            pop_front();
        } else{
            Node* temp = cola;
            cola = cola->prev;
            cola->next = head;
            head->prev = cola;
            delete temp;
        }
    }
    void remove(int pos){
        if (pos < 0 || pos >= size()) {
            cout << "Posición inválida" << endl;
            return;
        }
        if (pos == 0) {
            pop_front();
            return;
        }
        if (pos == size() - 1) {
            pop_back();
            return;
        }
        Node* curr = head;
        for (int i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
    }
    T operator[](int pos){
        if (!head) {
            cout << "Lista vacia" << endl;
            return -1;
        }
        if (pos < 0 || pos >= size()) {
            cout << "Posición inválida" << endl;
            return T();
        }
        Node* curr = head;
        for (int i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    void clear(){
        while (!empty())pop_front();
    }

    void reverse(){
        if (empty()|| head == cola) return;

        Node* curr = head;
        Node* temp= nullptr;
        do {
            temp = curr->next;
            curr->next = curr->prev;
            curr->prev = temp;
            curr = temp;
        } while (curr != head);
        temp = head;
        head = cola;
        cola = temp;
    }

};


int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    CircularDLL<int> lista;
    lista.crearCDLLfromList(arr, n);

    cout << "Lista inicial: ";
    lista.imprimir();

    lista.insert(8, 3);
    cout << "insertar 8 en la pos 3: ";
    lista.imprimir();

    CircularDLL<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(0);
    cout<<"Nueva lista: ";
    list.imprimir();
    cout << "Front: " << list.front() << "\n";
    cout << "Back: " << list.back() << "\n";

    list.insert(10, 2);
    cout << "Inserto 10 en posicion 2: ";
    list.imprimir();
    cout << "Elemento en la posicion 2: " << list[2] << "\n";

    cout<<"Remuevo el elemento de la pos 2: ";
    list.remove(2);
    list.imprimir();
    cout << "Elemento en posicion 2: " << list[2] << "\n";

    list.reverse();
    cout << "Revierto la lista: "; list.imprimir();

    list.clear();
    cout << "Tamano luego de clear: " << list.size() << "\n";

    return 0;
}
