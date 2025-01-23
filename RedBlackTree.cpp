#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

RedBlackTree::RedBlackTree() : root(nullptr) {}

void RedBlackTree::rotateLeft(Node*& x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node*& x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != nullptr)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(Node*& node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }

                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        else {
            Node* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::fixDelete(Node*& node) {
    while (node != root && (node == nullptr || node->color == BLACK)) {
        if (node == nullptr)
            			return;
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }

            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            }
            else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;

                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;

                if (sibling->right != nullptr)
                    sibling->right->color = BLACK;

                rotateLeft(node->parent);
                node = root;
            }
        }
        else {
            Node* sibling = node->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }

            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            }
            else {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;

                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;

                if (sibling->left != nullptr)
                    sibling->left->color = BLACK;

                rotateRight(node->parent);
                node = root;
            }
        }
    }
    if (node != nullptr)
        node->color = BLACK;
}

void RedBlackTree::insert(const string& name, const string& phone) {
    Node* newNode = new Node(name, phone);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (newNode->name < x->name)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;

    if (y == nullptr)
        root = newNode;
    else if (newNode->name < y->name)
        y->left = newNode;
    else
        y->right = newNode;

    fixInsert(newNode);
}

void RedBlackTree::remove(const string& name) {
    //de implementat
}

void RedBlackTree::listContacts() {
    if (root == nullptr) {
        cout << "No contacts to display.\n";
        return;
    }

    cout << "Contact List (sorted by name):\n";
    listContacts(root);
}

void RedBlackTree::listContacts(Node* node) {
    if (node == nullptr) {
        return; 
    }

    listContacts(node->left);
    cout << "Name: " << node->name << ", Phone: " << node->phone << "\n";

    listContacts(node->right);
}

Node* RedBlackTree::search(Node* node, const std::string& name) const {
    if (node == nullptr || node->name == name) {
        return node;
    }

    if (name < node->name) {
        return search(node->left, name);
    }
    else {
        return search(node->right, name);
    }
}

string RedBlackTree::search(const string& name) const {
    Node* result = search(root, name);
    return (result != nullptr) ? result->phone : ""; 
}

void RedBlackTree::visualizeTree() const {
    if (root == nullptr) {
        cout << "The tree is empty.\n";
        return;
    }
    visualizeTree(root, 0);
}
void RedBlackTree::visualizeTree(Node* node, int indent) const {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        cout << "  ";
    }
    cout << node->name << " (" << node->phone << ") ";
    if (node->color == RED) {
        cout << "[RED]";
    }
    else {
        cout << "[BLACK]";
    }
    cout << "\n";

    if (node->left != nullptr || node->right != nullptr) {
        visualizeTree(node->left, indent + 1);
        visualizeTree(node->right, indent + 1);
    }
}
void RedBlackTree::insertRomanianContacts() {
    insert("Andrei", "0741234567");
    insert("Bianca", "0752345678");
    insert("Cristian", "0763456789");
    insert("Daciana", "0774567890");
    insert("Elena", "0785678901");
    insert("Florin", "0796789012");
    insert("Gheorghe", "0701890123");
    insert("Irina", "0712901234");
    insert("Jorge", "0723012345");
    insert("Katalin", "0734123456");
}