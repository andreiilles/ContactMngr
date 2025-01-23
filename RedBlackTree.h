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
    void listContacts(Node* node);

    void visualizeTree(Node* node, int indent) const;
public:
    RedBlackTree();

    void insert(const string& name, const string& phone);
    void remove(const string& name);
    string search(const string& name) const;
    void listContacts();
    void visualizeTree() const;
    void insertRomanianContacts();
};
