#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    static const int DEFAULT_SIZE = 5;
    static constexpr double MAX_FILL_FACTOR = 0.7;
    vector<list<pair<K, V>>> table;
    int capacity;
    int size;
    int a, b, p; // Parámetros para el hash universal

    int universalHash(const K& key) const {
        unsigned long hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % p; // Hash polinómico mod p
        }
        return ((a * hash + b) % p) % capacity;
    }
    double getFillFactor() const {
        return static_cast<double>(size) / capacity;
    }
    void rehash() {
        int newCapacity = capacity * 2;
        vector<list<pair<K, V>>> newTable(newCapacity);

        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                unsigned long hash = 0;
                for (char ch : pair.first) {
                    hash = (hash * 31 + ch) % p; // Recalcular hash con los mismos parámetros
                }
                int newIndex = ((a * hash + b) % p) % newCapacity;
                newTable[newIndex].emplace_back(pair.first, pair.second);
            }
        }

        table = move(newTable);
        capacity = newCapacity;
    }

public:
    HashTable(int size = DEFAULT_SIZE) : capacity(size), size(0) {
        table.resize(capacity);
        p = 2147483647; // Un número primo grande
        a = 1 + rand() % (p - 1);
        b = rand() % p;
    }

    void insert(const K& key, const V& value) {
        if (getFillFactor() >= MAX_FILL_FACTOR) {
            rehash();
        }

        int index = universalHash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Reemplaza el valor si la clave ya existe
                return;
            }
        }
        table[index].emplace_back(key, value);
        size++;
    }

    bool search(const K& key, V& value) {
        int index = universalHash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    void remove(const K& key) {
        int index = universalHash(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                size--;
                return;
            }
        }
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            for (auto& pair : table[i]) {
                cout << "[" << pair.first << " : " << pair.second << "] ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable<string, int> ht(5);

    ht.insert("Alice", 25);
    ht.insert("Bob", 30);
    ht.insert("Charlie", 35);
    ht.insert("Dave", 40);
    ht.insert("Eve", 45);
    ht.insert("Frank", 50);

    ht.print();

    int age;
    if (ht.search("Bob", age)) {
        cout << "Edad de Bob: " << age << endl;
    } else {
        cout << "Bob no encontrado." << endl;
    }

    ht.remove("Charlie");
    ht.print();

    return 0;
}

/*
División
    k % m
    k-> clave, m->tam tabla hash (primo)
int divisionHash(int key, int tableSize) {
    return key % tableSize;
}


Multiplicación
    (A*k % 2^w) >> (m-r)
    m = 2^r
int multiplicationHash(int key, int tableSize) {
    const double A = 0.6180339887; // Número recomendado (razón áurea)
    double fracPart = key * A - (int)(key * A); // Parte fraccionaria
    return (int)(tableSize * fracPart);
}


Universal
    ([a*k + b] % p) % m
    a, b -> enteros aleatorios 0<a<p y 0<=b<p
    p -> primo grande > m
    m -> tamaño tabla hash
probabilidad colisión es 1/m


*/