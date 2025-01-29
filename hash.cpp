#include <iostream>
#include <vector>
#include <utility>
#include <random>

// Nodo para manejar colisiones con listas enlazadas
struct Node {
    std::string key;
    int value;
    Node* next;
    Node(std::string k, int v) : key(k), value(v), next(nullptr) {}
};

class HashMap {
private:
    static const int TABLE_SIZE = 10; // Tamaño de la tabla hash
    Node* table[TABLE_SIZE];
    int a, b, p;

    // Genera coeficientes para la función hash universal
    void initializeHash() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, p - 1);
        a = dist(gen);
        b = dist(gen);
    }

    // Función de hash universal
    int hashFunction(std::string key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % p;
        }
        return ((a * hash + b) % p) % TABLE_SIZE;
    }

public:
    HashMap() : p(101) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
        initializeHash();
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current) {
                Node* prev = current;
                current = current->next;
                delete prev;
            }
        }
    }

    void insert(std::string key, int value) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    int at(std::string key) {
        return get(key);
    }

    int get(std::string key) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        throw std::runtime_error("Key not found");
    }

    void remove(std::string key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool empty() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i]) return false;
        }
        return true;
    }

    size_t bucket_count() {
        return TABLE_SIZE;
    }

    size_t bucket(std::string key) {
        return hashFunction(key);
    }

    size_t bucket_size(size_t index) {
        size_t count = 0;
        Node* current = table[index];
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    int count(std::string key) {
        int index = hashFunction(key);
        Node* current = table[index];
        int occurrences = 0;
        while (current) {
            if (current->key == key) {
                occurrences++;
            }
            current = current->next;
        }
        return occurrences;
    }

    Node* find(std::string key) {
        int index = hashFunction(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    std::pair<Node*, Node*> equal_range(std::string key) {
        return std::make_pair(find(key), nullptr);
    }

    void erase(std::string key) {
        remove(key);
    }

    void iterate() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current) {
                std::cout << "Key: " << current->key << " Value: " << current->value << std::endl;
                current = current->next;
            }
        }
    }
};

int main() {
    HashMap map;
    map.insert("clave1", 10);
    map.insert("clave2", 20);
    map.insert("clave3", 30);

    std::cout << "clave1: " << map.at("clave1") << std::endl;
    std::cout << "clave2: " << map.get("clave2") << std::endl;

    map.erase("clave1");

    try {
        std::cout << "clave1: " << map.get("clave1") << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Bucket count: " << map.bucket_count() << std::endl;
    std::cout << "Is empty: " << map.empty() << std::endl;

    std::cout << "Iterating over hashmap:" << std::endl;
    map.iterate();

    return 0;
}
