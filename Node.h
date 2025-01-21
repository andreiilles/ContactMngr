#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;
enum Color { RED, BLACK };

class Node {
public:
    string name;       
    string phone;      
    Color color;            
    Node* left;             
    Node* right;           
    Node* parent;           

    Node(const string& name, const string& phone)
        : name(name), phone(phone), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

#endif // NODE_H
