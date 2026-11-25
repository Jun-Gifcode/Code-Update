#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    Node* insert(Node*& node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        else {
            cout << "Value " << value << " already exists in the tree." << endl;
        }
        return node;
    }

    bool search(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (value == node->data) {
            return true;
        }
        else if (value < node->data) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node*& node, int value) {
        if (node == nullptr) {
            return nullptr;
        }
        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

void display(Node* node) {
    if (node != nullptr) {
        display(node->left);
        cout << node->data << " ";
        display(node->right);
    }
}

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    bool search(int value) {
        if (search(root, value)) {
            cout << "Value " << value << " found in the tree." << endl;
            return true;
        }
        else {
            cout << "Value " << value << " not found in the tree." << endl;
            return false;
        }
    }

    void remove(int value) {
        if (!search(root, value)) {
            cout << "Value " << value << " not found in the tree. Cannot remove." << endl;
            return;
        }
        root = remove(root, value);
        cout << "Value " << value << " removed from the tree." << endl;
    }

    void display() {
        cout << "Binary Tree: ";
        display(root);
        cout << endl;
    }
};

int main(){

    BinaryTree tree;

    int values[] = {23, 45, 12, -5, 35, -45, 78};
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < numValues; i++) {
        tree.insert(values[i]);
    }

    cout <<"Initial tree: ";
    tree.display();

    int value;

    cout << "Enter a value to insert: ";
    cin >> value;
    tree.insert(value);
    tree.display();

    cout << "Enter a value to search: ";
    cin >> value;
    tree.search(value);

    cout << "Enter a value to remove: ";
    cin >> value;
    tree.remove(value);
    tree.display();

    return 0;
}