#include <iostream>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() {
        root = nullptr;
    }

    void insert(TreeNode* parent, int val, char side) {
        if (!parent) return;
        if (side == 'L' && !parent->left) {
            parent->left = new TreeNode(val);
        } else if (side == 'R' && !parent->right) {
            parent->right = new TreeNode(val);
        }
    }

    bool search(TreeNode* node, int key) {
        if (!node) return false;
        if (node->value == key) return true;
        return search(node->left, key) || search(node->right, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->value << " ";
        inorder(node->right);
    }

    void preorder(TreeNode* node) {
        if (!node) return;
        cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(TreeNode* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->value << " ";
    }

    TreeNode* remove(TreeNode* node, int key) {
        if (!node) return nullptr;

        if (node->value == key) {
            // sin hijos
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // un solo hijo
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            // dos hijos (reemplazamos con el nodo más derecho del subárbol izquierdo)
            TreeNode* temp = maxValueNode(node->left);
            node->value = temp->value;
            node->left = remove(node->left, temp->value);
        } else {
            node->left = remove(node->left, key);
            node->right = remove(node->right, key);
        }
        return node;
    }
    TreeNode* maxValueNode(TreeNode* node) {
        while (node->right) node = node->right;
        return node;
    }

    // Eliminar un nodo
    void remove(int key) {
        root = remove(root, key);
    }
    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void printTree(TreeNode* node, int space = 0, int count = 8) {
        if (!node) return;

        space += count;  // Incrementa el espacio en cada nivel

        // Imprimir primero el subárbol derecho
        printTree(node->right, space);

        // Imprimir el nodo actual con los espacios adecuados
        cout << endl;
        for (int i = count; i < space; i++) cout << " ";
        cout << node->value << "\n";

        // Imprimir el subárbol izquierdo
        printTree(node->left, space);
    }

    void printTree() {
        cout<<endl;
        printTree(root);
    }


    // Llamadas públicas para recorridos
    void printInorder() { inorder(root); cout << endl; }
    void printPreorder() { preorder(root); cout << endl; }
    void printPostorder() { postorder(root); cout << endl; }

    // Destructor
    ~BinaryTree() {
        deleteTree(root);
    }
};

// Ejemplo de uso
int main() {
    BinaryTree tree;
    tree.root = new TreeNode(1);

    tree.insert(tree.root, 2, 'L');
    tree.insert(tree.root, 3, 'R');
    tree.insert(tree.root->left, 4, 'L');
    tree.insert(tree.root->left, 5, 'R');
    tree.insert(tree.root->right, 6, 'L');
    tree.insert(tree.root->right, 7, 'R');

    cout << "Recorrido Inorden antes de eliminar: ";
    tree.printInorder();  // 4 2 5 1 6 3 7
    tree.printTree();

    // Búsqueda
    cout << "5 en el arbol? " << (tree.search(5) ? "Si" : "No") << endl;
    cout << "10 en el arbol? " << (tree.search(10) ? "Si" : "No") << endl;

    // Eliminación
    cout << "\nElimino 3 (con hijos)\n";
    tree.remove(3);
    tree.printInorder();  // 4 2 5 1 6 7
    tree.printTree();

    cout << "\nElimino 4 (hoja)...\n";
    tree.remove(4);
    tree.printInorder();  // 2 5 1 6 7

    tree.printTree();

    return 0;
}
