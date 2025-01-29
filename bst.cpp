#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class BST{
    struct Node{
        T value;
        Node* left;
        Node* right;
        Node(T val) : value(val), left(nullptr), right(nullptr) {}
    };
    Node* root;
    void insert(Node*& node, T value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value < node->value)
            insert(node->left, value);
        else
            insert(node->right, value);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->value << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->value << " ";
    }

    void bfs() {//wnchura
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << curr->value << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(T value) {
        insert(root, value);
    }
    bool search(T key) {
        return search(root, key);
    }

    bool search(Node* node, T key) {
        if (!node) return false;
        if (node->value == key) return true;
        if (key < node->value) return search(node->left, key);
        return search(node->right, key);
    }
    void remove(T key) {
        root = remove(root, key);
    }

    Node* remove(Node* node, T key) {
        if (!node) return nullptr;

        if (key < node->value) {
            node->left = remove(node->left, key);
        } else if (key > node->value) {
            node->right = remove(node->right, key);
        } else {
            // Uno o ningún hijo
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Dos hijos; busca el min en el sub derecho
            Node* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
        return node;
    }

    // nodo con menor valor en un subrbol
    Node* minValueNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }


    void printInorder() {
        inorder(root);
        cout << endl;
    }

    void printPreorder() {
        preorder(root);
        cout << endl;
    }

    void printPostorder() {
        postorder(root);
        cout << endl;
    }

    void printBFS() {
        bfs();
        cout << endl;
    }
};


int main(){
    BST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    cout << "Inorder antes de eliminar: ";
    tree.printInorder();    // 2 5 7 10 12 15 20

    cout << "\nBuscando 22: " << (tree.search(22) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando 7: " << (tree.search(7) ? "Encontrado" : "No encontrado") << endl;

    tree.printPreorder();   // 10 5 2 7 15 12 20
    tree.printPostorder();  // 2 7 5 12 20 15 10
    tree.printBFS();        // 10 5 15 2 7 12 20

    cout << "\nEliminando 5...\n";
    tree.remove(5);
    tree.printInorder();    // 2 7 10 12 15 20

    cout << "\nEliminando 10 (raiz)...\n";
    tree.remove(10);
    tree.printInorder();    // 2 7 12 15 20

    return 0;
}