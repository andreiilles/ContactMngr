#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Node.h"
#include <string>

using namespace std;

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void fixInsert(Node*& node);
    void fixDelete(Node*& node);
    Node* search(Node* node, const string& name) const;
    void inorderTraversal(Node* node) const;
    Node* minimum(Node* node);
    void listContacts(Node* node);
    void printTree(Node* node, int indent) const;
public:
    RedBlackTree();

    void insert(const string& name, const string& phone);
    void remove(const string& name);
    string search(const string& name) const;
    void listContacts();
    void visualizeTree() const;
    void insertRomanianContacts();
};

#endif // REDBLACKTREE_H
